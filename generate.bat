@echo off
cd make
premake5.exe --file=breakout.lua --fatal vs2019
cd ..
powershell "$s=(New-Object -COM WScript.Shell).CreateShortcut('%~dp0\Breakout.lnk');$s.TargetPath='%~dp0\.gen\prj\Breakout.sln';$s.Save()"
@echo Done