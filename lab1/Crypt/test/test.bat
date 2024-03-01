set PROGRAM="%~1"

rem Encrypting and decrypting a large file
%PROGRAM% crypt "data\test1\input.txt" "%TEMP%\crypted.txt" 120
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt "%TEMP%\crypted.txt" "%TEMP%\decrypted.txt" 120
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\decrypted.txt" "data\test1\input.txt" > nul
if ERRORLEVEL 1 goto err

rem Invalid decryption key
%PROGRAM% crypt "data\test1\input.txt" "%TEMP%\crypted.txt" 120
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt "%TEMP%\crypted.txt" "%TEMP%\decrypted.txt" 1
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\decrypted.txt" "data\test1\input.txt" > nul
if NOT ERRORLEVEL 1 goto err

rem Invalid key format
%PROGRAM% crypt "data\test1\input.txt" "%TEMP%\crypted.txt" 256
if NOT ERRORLEVEL 1 goto err

rem Invalid key format
%PROGRAM% crypt "data\test1\input.txt" "%TEMP%\crypted.txt" -1
if NOT ERRORLEVEL 1 goto err

rem Invalid key format
%PROGRAM% crypt "data\test1\input.txt" "%TEMP%\crypted.txt" abcd
if NOT ERRORLEVEL 1 goto err

rem Invalid mode
%PROGRAM% test "data\test1\input.txt" "%TEMP%\crypted.txt" 20
if NOT ERRORLEVEL 1 goto err

rem File not exists
%PROGRAM% crypt "test.txt" "%TEMP%\crypted.txt" 20
if NOT ERRORLEVEL 1 goto err

rem Empty file
%PROGRAM% crypt "data\test2\input.txt" "%TEMP%\crypted.txt" 120
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt "%TEMP%\crypted.txt" "%TEMP%\decrypted.txt" 120
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\decrypted.txt" "data\test2\input.txt" > nul
if ERRORLEVEL 1 goto err

rem Cannot open exists output file
%PROGRAM% crypt "data\test2\input.txt" "./Crypt.exe" 20
if NOT ERRORLEVEL 1 goto err

rem Binary file
%PROGRAM% crypt Crypt.exe "%TEMP%\crypted" 120
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt "%TEMP%\crypted" "%TEMP%\decrypted" 120
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\decrypted" Crypt.exe > nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1