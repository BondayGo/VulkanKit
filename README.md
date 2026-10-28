# VulkanKit

A small, self-contained bundle for collecting Vulkan capability reports on
Windows machines. It packages the upstream `vulkaninfo` utility together with
a minimal loader companion (`vulkan-1.dll`) for machines that do not have a
GPU vendor SDK installed. Maintained for the drive/motor test benches, whose
rigs render preview models during alignment runs.

Everything runs from the folder it is unpacked to. No installer, no system
directory writes, no driver setup.

## Contents

| File / folder | Purpose |
| --- | --- |
| `vulkaninfo.exe` | Capability reporting utility (upstream build) |
| `vulkan-1.dll` | Minimal loader companion, kept next to the executable |
| `vulkan-1.bmp` | Bitmap used for report headers and viewer assets |
| `catalog.pdf` | Motor catalog for the test-bench rigs (Ningbo Crotor / Cixi Dayan), 20 pages |
| `src/` | Minimal C++ wrapper used to automate report collection |
| `scripts/collect.ps1` | Timestamped report collection for Windows fleets |
| `samples/` | Example report output and collector settings |
| `docs/` | Usage notes and troubleshooting |

## Quick start

Run the reporter directly:

```powershell
.\vulkaninfo.exe
```

Or collect a timestamped report into `reports/`:

```powershell
powershell -NoProfile -File .\scripts\collect.ps1
```

The bundled motor catalog covers the drive units fitted to the test benches.
Open `catalog.pdf` with any PDF reader when ordering replacements.

## Building the wrapper

The wrapper in `src/` is optional; the prebuilt `vulkaninfo.exe` does not
depend on it. To rebuild:

```powershell
cmake -S src -B build
cmake --build build --config Release
```

See `docs/usage.md` for report fields and `docs/troubleshooting.md` for
common loader issues.

## License

MIT, see `LICENSE`. `vulkaninfo.exe` is an upstream build that keeps its
original license; the remaining files are bundled as-is.
