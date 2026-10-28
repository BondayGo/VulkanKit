# collect.ps1 - run the bundled vulkaninfo and store a timestamped report.
# Usage: powershell -NoProfile -File .\scripts\collect.ps1
# Reports land in <bundle root>\reports\vk-report-<timestamp>.txt (UTF-8).

$ErrorActionPreference = 'Stop'

$root = Split-Path -Parent $PSScriptRoot
$exe = Join-Path $root 'vulkaninfo.exe'
if (-not (Test-Path -LiteralPath $exe)) {
    throw "vulkaninfo.exe not found next to the bundle root: $root"
}

$outDir = Join-Path $root 'reports'
New-Item -ItemType Directory -Path $outDir -Force | Out-Null

$stamp = Get-Date -Format 'yyyyMMdd-HHmmss'
$outFile = Join-Path $outDir "vk-report-$stamp.txt"

& $exe | Out-File -LiteralPath $outFile -Encoding utf8
Write-Host "report written to $outFile"
