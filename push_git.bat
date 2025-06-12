@echo on
F:
cd F:\zwm\workspace\unix_book_code
git status -s
git add .
for /f "tokens=1-4 delims=/ " %%a in ('date /t') do (set mydate=%%a-%%b-%%c)
for /f "tokens=1-3 delims=:." %%a in ('echo %time%') do (set mytime=%%a:%%b:%%c)
git commit -m  "%mydate% %mytime%"
@echo off
for /L %%i in (1,1,100) do (
    setlocal enabledelayedexpansion
    git push origin master
    if !errorlevel! == 0 (
        echo "push to git success."
	pause
        exit
    ) else (
        echo "push to git fail~~~retry ..."
    )
)

pause