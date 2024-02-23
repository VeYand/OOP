set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem Nothing to replace
%PROGRAM% data\test1\input.txt "%TEMP%\output.txt" bird cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" data\test1\output.txt >nul
if ERRORLEVEL 1 goto err

rem Successful replacement for one line
%PROGRAM% data\test2\input.txt "%TEMP%\output.txt" dog cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" data\test2\output.txt >nul
if ERRORLEVEL 1 goto err

rem Replacement for adjustment 1231234 in line 12312312345
%PROGRAM% data\test3\input.txt "%TEMP%\output.txt" 1231234 1234
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" data\test3\output.txt >nul
if ERRORLEVEL 1 goto err

rem Empty input file
%PROGRAM% data\test4\input.txt "%TEMP%\output.txt" 1231234 cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" data\test4\output.txt >nul
if ERRORLEVEL 1 goto err

rem Successful replacement for multiline file
%PROGRAM% data\test5\input.txt "%TEMP%\output.txt" field ABCD
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" data\test5\output.txt >nul
if ERRORLEVEL 1 goto err

rem Successful replacement in a large multiline file
%PROGRAM% data\test6\input.txt "%TEMP%\output.txt" elit word
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" data\test6\output.txt >nul
if ERRORLEVEL 1 goto err

rem Missing command line argument
%PROGRAM% data\test5\input.txt "%TEMP%\output.txt" field
echo %ERRORLEVEL%
if NOT ERRORLEVEL 1 goto err

rem Nonexistent file
%PROGRAM% data\qwerty.txt "%TEMP%\output.txt" field field
if NOT ERRORLEVEL 1 goto err

rem Invalid output file
%PROGRAM% data\test5\input.txt ./Replace.exe field field
if NOT ERRORLEVEL 1 goto err

rem Empty search string
%PROGRAM% data\test6\input.txt "%TEMP%\output.txt" "" word
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" data\test6\input.txt >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1
