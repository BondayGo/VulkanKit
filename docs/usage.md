# Usage notes

## Running the reporter

`vulkaninfo.exe` enumerates every Vulkan physical device visible to the
loader and prints its properties to stdout:

```powershell
.\vulkaninfo.exe
.\vulkaninfo.exe --summary
```

Keep `vulkan-1.dll` in the same directory as the executable. The companion
DLL is resolved from the application directory first, so the bundle does not
depend on a system-wide Vulkan runtime.

## Report contents

A typical report contains:

- **Instance properties**: loader API version and available instance layers.
- **Device properties**: device name, vendor/device IDs, driver version, and
  the supported Vulkan API version per physical device.
- **Queue families**: graphics/compute/transfer flags and queue counts.
- **Memory heaps**: device-local and host-visible heap sizes.
- **Surface support**: present modes and formats when a windowing system is
  available.

The JSON samples under `samples/` show the condensed form planned for the
next collector revision; the current `collect.ps1` writes plain-text reports.
`samples/settings.ini` documents that planned schema.

## The motor catalog

`catalog.pdf` is the motor catalog for the drive units on the test benches
(Ningbo Crotor / Cixi Dayan). Keep it with the bundle so replacement orders
can be checked without leaving the rig.

## Collection on multiple machines

`scripts/collect.ps1` writes `reports/vk-report-<timestamp>.txt` next to the
bundle. Schedule it or invoke it through your usual remote execution tooling;
no elevation is required for a basic capability report.
