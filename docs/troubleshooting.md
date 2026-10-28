# Troubleshooting

## "vulkan-1.dll was not found"

The companion DLL must sit next to `vulkaninfo.exe`. If you moved the
executable out of the bundle, copy `vulkan-1.dll` along with it or restore
the original layout. On bench machines the full SDK is usually installed
system-wide, so a missing bundle DLL only matters on clean Windows images.

## "No Vulkan devices found" / instance creation fails

- The machine has no Vulkan-capable GPU driver installed. Install the vendor
  driver (NVIDIA/AMD/Intel) and rerun.
- Remote Desktop sessions sometimes expose only a software device. Check the
  device name in the report; `llvmpipe` or `SwiftShader` entries indicate
  software rendering.
- On laptops with hybrid graphics, the report may list both the integrated
  and the discrete adapter. This is expected.

## Empty or truncated reports

- Run from a local directory. Some endpoint products block executable launches
  from network shares, which results in partial output.
- If the console closes immediately, run from an existing terminal instead of
  double-clicking, so the error text stays visible.
- Very old drivers (pre-2018) may fail mid-enumeration. The report up to the
  failure point is still useful; older rig GPUs are known to stop after the
  memory heap section.

## Encoding issues in saved reports

Use `scripts/collect.ps1`, which writes UTF-8. Redirecting with `>` in
`cmd.exe` produces UTF-16 on some systems and confuses downstream parsers.
