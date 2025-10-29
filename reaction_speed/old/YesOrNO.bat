@echo off
setlocal ENABLEDELAYEDEXPANSION

rem Generate a random 0 or 1 using %RANDOM%
set /a pick=%RANDOM% %% 2

cls
echo.
echo ==============================
echo        The answer is:
echo ==============================
echo.

if %pick%==0 (
    echo Yes
) else (
    echo No
)

echo.
pause
endlocal