@echo off

SET "VSCMD_START_DIR=%CD%"
CALL "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

SETLOCAL enabledelayedexpansion

REM Executable
SET EXECUTABLE_NAME=milsh.exe

REM Directories
FOR %%A IN ("%~dp0.") DO SET PROJECT_FOLDER=%%~dpA
SET PROJECT_FOLDER=%PROJECT_FOLDER:\=/%
SET SRC_DIR=source
SET OBJ_DIR=build\obj\win32
SET BIN_DIR=build\bin\win32
IF NOT EXIST %OBJ_DIR% MD %OBJ_DIR%
IF NOT EXIST %BIN_DIR% MD %BIN_DIR%

REM Defines
SET COMMON_DEFINES=/D__WIN32__ /D__win32__ /D_AMD64_ /DNOMINMAX

REM Includes
SET PROJECT_INCLUDES=/I%SRC_DIR%

REM Switches
SET WARNING_SWITCHES=/W4
SET COMMON_SWITCHES=/c /std:c17 /nologo /WL /MDd %WARNING_SWITCHES% /Od /Fo%OBJ_DIR%\
SET DEBUG_SWITCHES=/Od /Fdbuild\bin\win32\milsh /Zi 
SET SWITCHES=%COMMON_SWITCHES% %DEBUG_SWITCHES% %COMMON_DEFINES% %PROJECT_INCLUDES%

REM Files
SET FILE_NAMES=milsh
SET FILES=
(for %%c in (%FILE_NAMES%) do (
	set "FILES=!FILES_C!%SRC_DIR%\%%c.cpp "
))

echo == Compile...
cl %SWITCHES% %FILES%
IF %ERRORLEVEL%==0 (goto link) ELSE (goto bad)

:link
echo == Link...
link /NOLOGO /DEBUG /INCREMENTAL:NO /SUBSYSTEM:CONSOLE /ENTRY:WinMainCRTStartup^
 %OBJ_DIR%\milsh.obj /OUT:%BIN_DIR%\%EXECUTABLE_NAME%
IF NOT %ERRORLEVEL%==0 (goto bad)

REM Write compile commands database
SET LAST_FILE=
(for %%i in (%FILE_NAMES%) do ( 
	SET LAST_FILE=%%i
))

echo == Generate compile_commands.json...
echo [>compile_commands.json
(for %%f in (%FILE_NAMES%) do ( 
	echo     {>>compile_commands.json
	set SWITCHES=!SWITCHES:\=/!
	echo         "command": "cl !SWITCHES!",>>compile_commands.json
	echo         "directory": "%PROJECT_FOLDER%",>>compile_commands.json
	echo         "file": "source/%%f.cpp">>compile_commands.json
	IF %%f==%LAST_FILE% echo     }>>compile_commands.json
	IF NOT %%f==%LAST_FILE% echo     },>>compile_commands.json
))
echo ]>>compile_commands.json

:good
	echo ======================================================================
	echo == Build state: SUCCESSFULL
	echo ======================================================================
	goto end

:bad
	echo ======================================================================
	echo == Build state: FAILED
	echo ======================================================================
	goto end

:end

endlocal

