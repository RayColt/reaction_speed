@echo off
title Reaction Time Test (R Key) - CMD Only
cls

echo =================================================================
echo   REACTION TIME TEST (R KEY) - PURE CMD
echo =================================================================
echo.
echo NOTE ON PRECISION:
echo Pure Batch/CMD cannot reliably measure time in milliseconds (ms).
echo This test measures time in centiseconds (1/100th of a second)
echo.
echo INSTRUCTIONS:
echo 1. Wait for the screen to clear and the large 'O' to appear.
echo 2. Press the R key immediately when the 'O' appears.
echo.
echo Press any key to start the test...
pause >nul
cls

:: --- SETUP RANDOM DELAY (3 to 6 seconds) ---
:: Generates a random number between 3 and 6
set /a "RAND_SEC=(%random%%%4)+3"

echo Preparing... O will appear in %RAND_SEC% seconds...
echo Press the R key immediately.
timeout /t %RAND_SEC% /nobreak >nul
cls

:: --- STIMULUS AND TIMING ---

:: 1. Capture Start Time in Centiseconds
call :GetCentiseconds START_TIME

:: 2. Display Stimulus
echo.
echo   OOOOOO
echo   O    O
echo   O    O
echo   O    O
echo   OOOOOO
echo.

:: 3. Wait for 'R' key press (CHOICE returns errorlevel 1 for the first option 'R')
choice /C RC /N /M "Press R to react..."

:: 4. Capture End Time in Centiseconds
call :GetCentiseconds END_TIME

:: --- CALCULATION ---

set /a REACTION_CS=END_TIME-START_TIME

:: Handle wrap-around hour change (only if the reaction was truly slow, spanning an hour change)
if %REACTION_CS% LSS 0 (
:: 360000 centiseconds = 1 hour (3600 seconds * 100)
set /a REACTION_CS=REACTION_CS+360000
)

:: --- OUTPUT ---
cls
echo =================================================================
echo                       T E S T   C O M P L E T E
echo =================================================================
echo.
echo Your measured reaction time:
echo.
echo             %REACTION_CS% centiseconds (cs)
echo.
echo Remember: This is low precision (1/100th second).
echo.
echo Your US Army S indication is %REACTION_CS% divided by 10
echo =================================================================
echo.
echo Press any key to exit...
pause >nul
exit /b

:: --- SUBROUTINE TO CONVERT HH:MM:SS.xx TO CENTISECONDS ---
:GetCentiseconds
:: This subroutine converts the system time (HH:MM:SS.xx) into a single integer
:: representing the total number of centiseconds since the last hour change.
:: Input: (none)
:: Output: %1 (variable name to store result)
setlocal
:: Replace leading space in time string with zero (e.g., " 9:..." becomes "09:...")
set "time_var=%time: =0%"

:: Extract time components
set "H=%time_var:~0,2%"
set "M=%time_var:~3,2%"
set "S=%time_var:~6,2%"
set "C=%time_var:~9,2%"

:: Calculate total centiseconds: (Hours * 360000) + (Minutes * 6000) + (Seconds * 100) + Centiseconds
set /a TotalCS=(H*360000)+(M*6000)+(S*100)+C

:: Return the value to the calling context
endlocal & set "%1=%TotalCS%"

exit /b