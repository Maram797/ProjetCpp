@echo off
set PATH=C:\Qtt\6.7.3\mingw_64\bin;C:\Qtt\Tools\mingw1120_64\bin;%PATH%
cd /D c:\Users\ASUS\Desktop\Qt\GestionCommandes
if not exist build mkdir build
cd build
qmake ..\GestionCommandes.pro > build_log.txt 2>&1
mingw32-make >> build_log.txt 2>&1
type build_log.txt
