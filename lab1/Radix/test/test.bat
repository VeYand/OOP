set PROGRAM="%~1"

rem Empty value
%PROGRAM% 2 10 "" > nul
if NOT ERRORLEVEL 1 goto err

rem Incorrect radix
%PROGRAM% 37 10 123 > nul
if NOT ERRORLEVEL 1 goto err

rem Incorrect radix
%PROGRAM% 10 37 123 > nul
if NOT ERRORLEVEL 1 goto err

rem Incorrect value
%PROGRAM% 2 10 XYZ > nul
if NOT ERRORLEVEL 1 goto err

rem Successful conversion from binary to decimal
%PROGRAM% 2 10 1010 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
echo 10> "%TEMP%\expected.txt"
fc.exe "%TEMP%\output.txt" "%TEMP%\expected.txt" > nul
if ERRORLEVEL 1 goto err

rem Successful conversion from hexadecimal to decimal
%PROGRAM% 16 10 1F > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
echo 31> "%TEMP%\expected.txt"
fc.exe "%TEMP%\output.txt" "%TEMP%\expected.txt" > nul
if ERRORLEVEL 1 goto err

rem Successful conversion from decimal to binary
%PROGRAM% 10 2 10 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
echo 1010> "%TEMP%\expected.txt"
fc.exe "%TEMP%\output.txt" "%TEMP%\expected.txt" > nul
if ERRORLEVEL 1 goto err

rem Successful conversion from decimal to thirty-decimal system
%PROGRAM% 10 30 31 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
echo 11> "%TEMP%\expected.txt"
fc.exe "%TEMP%\output.txt" "%TEMP%\expected.txt" > nul
if ERRORLEVEL 1 goto err

rem Successful conversion from binary to ternary system
%PROGRAM% 2 3 1010 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
echo 101> "%TEMP%\expected.txt"
fc.exe "%TEMP%\output.txt" "%TEMP%\expected.txt" > nul
if ERRORLEVEL 1 goto err

rem Successful conversion from hexadecimal to binary
%PROGRAM% 16 2 1F > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
echo 11111> "%TEMP%\expected.txt"
fc.exe "%TEMP%\output.txt" "%TEMP%\expected.txt" > nul
if ERRORLEVEL 1 goto err

rem Conversion from decimal to binary zero
%PROGRAM% 10 2 0 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
echo|set /p="0"> "%TEMP%\expected.txt"
fc.exe "%TEMP%\output.txt" "%TEMP%\expected.txt" > nul
if ERRORLEVEL 1 goto err

rem Conversion from binary to decimal zero
%PROGRAM% 2 10 0 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
echo|set /p="0"> "%TEMP%\expected.txt"
fc.exe "%TEMP%\output.txt" "%TEMP%\expected.txt" > nul
if ERRORLEVEL 1 goto err

rem from hexadecimal system to thirty-digit system
%PROGRAM% 16 30 FFFFFFF > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
echo B1C1IF> "%TEMP%\expected.txt"
fc.exe "%TEMP%\output.txt" "%TEMP%\expected.txt" > nul
if ERRORLEVEL 1 goto err

rem A very large number
%PROGRAM% 10 2 99999999999999999999999999999999999999999999 > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

rem A very large number in the hexadecimal system
%PROGRAM% 16 36 FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

rem There are not enough command line arguments
%PROGRAM% 10 2 > nul
if NOT ERRORLEVEL 1 goto err

rem Successful conversion from negative binary to decimal
%PROGRAM% 2 10 "-1010" > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
echo -10> "%TEMP%\expected.txt"
fc.exe "%TEMP%\output.txt" "%TEMP%\expected.txt" > nul
if ERRORLEVEL 1 goto err

rem Successful conversion from negative hexadecimal to binary
%PROGRAM% 16 2 -1F > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
echo -11111> "%TEMP%\expected.txt"
fc.exe "%TEMP%\output.txt" "%TEMP%\expected.txt" > nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1