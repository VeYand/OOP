set PROGRAM="%~1"

rem Valid operation of the program
%PROGRAM% data/test1/input.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" data/test1/output.txt
if ERRORLEVEL 1 goto err

rem An area with a gap
%PROGRAM% data/test2/input.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" data/test2/output.txt > nul
if ERRORLEVEL 1 goto err

rem Checking the cropping of the input field
%PROGRAM% data/test3/input.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" data/test3/output.txt > nul
if ERRORLEVEL 1 goto err

rem An empty file
%PROGRAM% data/test4/input.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" data/test4/output.txt > nul
if ERRORLEVEL 1 goto err

rem A field without fill points
%PROGRAM% data/test5/input.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" data/test5/output.txt > nul
if ERRORLEVEL 1 goto err

rem Ignoring unidentified characters
%PROGRAM% data/test6/input.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" data/test6/output.txt > nul
if ERRORLEVEL 1 goto err

rem Non-existent file
%PROGRAM% data/test777/input.txt "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

rem Not enough parameters
%PROGRAM%
if NOT ERRORLEVEL 1 goto err

rem Cannot open exists output file
%PROGRAM% data\test2\input.txt ./Fill.exe
if NOT ERRORLEVEL 1 goto err

rem Точка начала окружена стенами
%PROGRAM% data/test7/input.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" data/test7/output.txt > nul
if ERRORLEVEL 1 goto err

rem Точка начала окружена точками начала
%PROGRAM% data/test8/input.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" data/test8/output.txt > nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1