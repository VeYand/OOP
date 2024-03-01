set PROGRAM="%~1"

rem Successful run №1
%PROGRAM% data/test1/input.txt > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt"  data/test1/output.txt > nul
if ERRORLEVEL 1 goto err

rem Successful run №2
%PROGRAM% data/test2/input.txt > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt"  data/test2/output.txt > nul
if ERRORLEVEL 1 goto err

rem The absence of an element in the row
%PROGRAM% data/test3/input.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

rem The absence of an element in the column
%PROGRAM% data/test4/input.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

rem Empty file
%PROGRAM% data/test5/input.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

rem Invalid data type in input
%PROGRAM% data/test6/input.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

rem The matrix does not have an inverse matrix
%PROGRAM% data/test7/input.txt > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
echo The matrix does not have an inverse matrix.> "%TEMP%\expected.txt"
fc.exe "%TEMP%\output.txt" "%TEMP%\expected.txt" > nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1