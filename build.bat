@echo off
call ..\code\custom\bin\buildsuper_x64-win.bat custom.cpp %*
copy custom_4coder.dll ..\build
copy custom_4coder.pdb ..\build