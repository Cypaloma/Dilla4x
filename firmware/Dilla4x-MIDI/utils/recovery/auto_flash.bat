@echo off
setlocal EnableDelayedExpansion

REM ========================================================================
REM  Dilla4x Recovery Auto-Flash for Windows
REM  Compiles and uploads recovery.ino to an ATmega32U4 (Pro Micro)
REM ========================================================================

REM Tunables (override via environment variables)
if not defined FQBN set FQBN=arduino:avr:micro
if not defined BUILD_DIR set BUILD_DIR=%~dp0build

echo [Recovery] Board: %FQBN%
echo [Recovery] Sketch: %~dp0
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

echo [Recovery] Compiling sketch...
arduino-cli compile --fqbn "%FQBN%" --output-dir "%BUILD_DIR%" "%~dp0"
if errorlevel 1 (
    echo [Recovery] Compilation failed.
    pause
    exit /b 1
)

REM Find the hex file
for %%f in ("%BUILD_DIR%\*.ino.hex") do set HEX=%%f
if not defined HEX (
    echo [Recovery] Hex file not found in %BUILD_DIR%
    pause
    exit /b 1
)
echo [Recovery] Hex: %HEX%

echo [Recovery] Scanning for COM ports... Double-tap reset if needed.

:scan_loop
REM List COM ports where Arduino may appear
for /f "tokens=1 delims=:" %%p in ('wmic path Win32_SerialPort get DeviceID 2^>nul ^| findstr "COM"') do (
    set PORT=%%p
    REM Trim whitespace
    set PORT=!PORT: =!
    
    if defined PORT (
        echo [Recovery] Trying port !PORT!...
        
        REM Attempt upload (retry 3 times)
        for /L %%n in (1,1,3) do (
            arduino-cli upload --fqbn "%FQBN%" --input-dir "%BUILD_DIR%" -p "!PORT!" "%~dp0" 2>nul
            if not errorlevel 1 (
                echo [Recovery] SUCCESS on !PORT!
                pause
                exit /b 0
            )
            timeout /t 1 /nobreak >nul
        )
        
        REM Trigger bootloader via mode command (1200 baud touch)
        mode !PORT!: baud=1200 >nul 2>&1
        timeout /t 1 /nobreak >nul
        
        REM Retry after bootloader trigger
        for /L %%n in (1,1,5) do (
            arduino-cli upload --fqbn "%FQBN%" --input-dir "%BUILD_DIR%" -p "!PORT!" "%~dp0" 2>nul
            if not errorlevel 1 (
                echo [Recovery] SUCCESS on !PORT!
                pause
                exit /b 0
            )
            timeout /t 1 /nobreak >nul
        )
    )
)

REM Short delay before rescanning
timeout /t 2 /nobreak >nul
goto scan_loop
