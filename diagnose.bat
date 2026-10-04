@echo off
REM ===== Build Script for GestionCommandes =====
set MINGW=C:\Users\ASUS\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin

REM Find qmake in Qt installation
set QMAKE=
for %%d in (
    "C:\Qt6\6.7.3\mingw_64\bin\qmake.exe"
    "C:\Qt\6.7.3\mingw_64\bin\qmake.exe"
    "C:\Qtt\6.7.3\mingw_64\bin\qmake.exe"
    "C:\Qt\qtcreator-20.0.2\bin\qmake.exe"
) do (
    if exist %%d set QMAKE=%%~d
)

echo QMAKE found: %QMAKE%
echo MINGW: %MINGW%

%MINGW%\g++.exe --version
