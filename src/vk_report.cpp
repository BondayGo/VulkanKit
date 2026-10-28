// vk_report.cpp - minimal wrapper around the bundled vulkaninfo executable.
//
// Runs vulkaninfo from the bundle root, captures stdout, and writes it to a
// timestamped text file under reports/. The wrapper is optional; the bundled
// vulkaninfo.exe works standalone.

#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>

namespace fs = std::filesystem;

namespace {

std::string Timestamp() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    localtime_s(&tm, &t);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y%m%d-%H%M%S", &tm);
    return buf;
}

// Runs vulkaninfo from the directory the wrapper is invoked in (or the
// explicit root passed as argv[1]), capturing stdout/stderr into `outFile`.
// Returns the exit code.
DWORD RunCaptured(const fs::path& exe, const fs::path& outFile) {
    SECURITY_ATTRIBUTES sa{};
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;

    HANDLE out = CreateFileW(outFile.c_str(), GENERIC_WRITE, FILE_SHARE_READ,
                             &sa, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (out == INVALID_HANDLE_VALUE) return ERROR_OPEN_FAILED;

    STARTUPINFOW si{};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = out;
    si.hStdError = out;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

    PROCESS_INFORMATION pi{};
    std::wstring cmd = L"\"" + exe.wstring() + L"\"";
    const BOOL ok = CreateProcessW(nullptr, cmd.data(), nullptr, nullptr, TRUE,
                                   CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi);
    CloseHandle(out);
    if (!ok) return GetLastError();

    WaitForSingleObject(pi.hProcess, 120000);
    DWORD code = 1;
    GetExitCodeProcess(pi.hProcess, &code);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return code;
}

}  // namespace

int wmain(int argc, wchar_t** argv) {
    // Default root is the current directory; an explicit root passed as
    // argv[1] wins (the in-tree comment above describes both paths).
    fs::path root = argc > 1 ? fs::path(argv[1]) : fs::current_path();
    const fs::path exe = root / L"vulkaninfo.exe";
    if (!fs::exists(exe)) {
        std::fprintf(stderr, "vulkaninfo.exe not found in %s\n",
                     root.string().c_str());
        return 2;
    }

    const fs::path outDir = root / L"reports";
    std::error_code ec;
    fs::create_directories(outDir, ec);
    const fs::path outFile = outDir / ("vk-report-" + Timestamp() + ".txt");

    const DWORD code = RunCaptured(exe, outFile);
    std::printf("report written to %s (exit %lu)\n", outFile.string().c_str(),
                static_cast<unsigned long>(code));
    return static_cast<int>(code);
}
