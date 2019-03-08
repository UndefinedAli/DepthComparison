@echo off
setlocal ENABLEDELAYEDEXPANSION

set /p a=InputCamNumID:


rd /q cam!a!
mkdir cam!a!

DIR PIC* /B >list.txt
set /a Num=1
for /f "delims=[" %%i in (list.txt) do (
echo !Num!
echo %%i
cd %%i
rem rename origin_5.jpg 56!Num!.jpg
rem #rename origin_6.jpg 65!Num!.jpg
copy origin_!a!.jpg ..\cam!a!\cam1_!Num!.jpg
set /a Num+=1
cd ..\
)