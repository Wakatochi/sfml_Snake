@echo off
setlocal

set "PROJECT_DIR=%~dp0.."
set "DOC_DIR=%PROJECT_DIR%\Release_Bin\doc"
set "SOURCE_FILE=%PROJECT_DIR%\latex\gdd.tex"
set "PDFLATEX=%LOCALAPPDATA%\Programs\MiKTeX\miktex\bin\x64\pdflatex.exe"
set "BUILD_LOG=%DOC_DIR%\gdd-build.log"

if not exist "%DOC_DIR%" mkdir "%DOC_DIR%"
if not exist "%PDFLATEX%" (
	echo [LaTeX] ERROR: pdflatex.exe was not found at "%PDFLATEX%".
	exit /b 1
)

"%PDFLATEX%" -interaction=nonstopmode -halt-on-error -output-directory="%DOC_DIR%" "%SOURCE_FILE%" > "%BUILD_LOG%" 2>&1
if errorlevel 1 (
	echo [LaTeX] ERROR: compilation failed.
	findstr /C:"! LaTeX Error:" /C:"! Package" /C:"!  ==> Fatal error" /C:"Emergency stop" "%BUILD_LOG%"
	echo [LaTeX] Full log: "%BUILD_LOG%"
	exit /b 1
)

echo [LaTeX] SUCCESS: generated "%DOC_DIR%\gdd.pdf".
endlocal
exit /b 0
