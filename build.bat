@echo off
:: call ..\code\custom\bin\buildsuper_x64-win.bat custom.cpp %*
:: copy custom_4coder.dll ..\build
:: copy custom_4coder.pdb ..\build
copy config.4coder ..\build
copy theme-sol-black.4coder ..\build\themes
copy theme-sol-slate.4coder ..\build\themes
