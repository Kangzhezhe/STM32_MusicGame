@echo off
setlocal enabledelayedexpansion
set "sourceDir=pics"
set "targetDir=image_bin"
set "pythonCmd=python.exe"

if not exist "%targetDir%" mkdir "%targetDir%"
for %%i in ("%sourceDir%*.png") do (
%pythonCmd% D:\linux\MusicGame\SD_rootLVGLImage.py --ofmt BIN --cf RGB565 --align 1 --compress NONE "%%i" -o "%targetDir%%%~nxi"
)

echo All PNG files have been converted to BIN and saved in "%targetDir%".

echo Copying .bin files to image_bin folder and removing subfolders…
@REM 把image_bin里面的子文件的bin提取到image_bin目录下，并删除子目录
for /D %%d in ("%targetDir%*") do (
for %%f in ("%%d*.bin") do (
copy "%%f" "%targetDir%"
)
rd "%%d" /S /Q
)

echo Cleanup completed. All .bin files are now in "%targetDir%" and subfolders removed.
pause