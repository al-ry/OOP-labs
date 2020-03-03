set PROGRAM="%~1"


%PROGRAM% packMode input.txt output.txt > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err

%PROGRAM% pack invalid.txt output.txt > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err

%PROGRAM% unpack invalid.txt output.txt > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err


rem Нечетная длина запакованного файла
%PROGRAM% unpack testing/not_even_packed_file.txt output.txt > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err

%PROGRAM% unpack testing/empty.txt %TEMP%\out.txt 
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/empty_out.txt
if ERRORLEVEL 1 goto err
echo Test 0 passed

%PROGRAM% pack testing/empty.txt %TEMP%\out.txt 
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/empty_out.txt
if ERRORLEVEL 1 goto err
echo Test 1 passed


rem Запаковка 255 байт
%PROGRAM% pack testing/unpacking1.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/packing1.txt
if ERRORLEVEL 1 goto err
echo Test 2 passed

rem Распаковка 255 байт
%PROGRAM% unpack testing/packing1.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/unpacking1.txt
if ERRORLEVEL 1 goto err
echo Test 3 passed

rem Запаковка 256 байт
%PROGRAM% pack testing/unpacking2.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/packing2.txt
if ERRORLEVEL 1 goto err
echo Test 4 passed

rem Распаковка 256 байт
%PROGRAM% unpack testing/packing2.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/unpacking2.txt
if ERRORLEVEL 1 goto err
echo Test 5 passed

rem Запаковка 257 байт
%PROGRAM% pack testing/unpacking3.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/packing3.txt
if ERRORLEVEL 1 goto err
echo Test 6 passed

rem Распаковка 257 байт
%PROGRAM% unpack testing/packing3.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/unpacking3.txt
if ERRORLEVEL 1 goto err
echo Test 7 passed

%PROGRAM% pack testing/unpacking4.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/packing4.txt
if ERRORLEVEL 1 goto err
echo Test 8 passed

%PROGRAM% unpack testing/packing4.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/unpacking4.txt
if ERRORLEVEL 1 goto err
echo Test 9 passed


rem Запаковка символа с кодом 255
%PROGRAM% pack testing/unpacking5.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/packing5.txt
if ERRORLEVEL 1 goto err
echo Test 10 passed


rem Распаковка символа с кодом 255
%PROGRAM% unpack testing/packing5.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/unpacking5.txt
if ERRORLEVEL 1 goto err
echo Test 11 passed

rem Запаковка 1 байта
%PROGRAM% pack testing/unpacking6.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/packing6.txt
if ERRORLEVEL 1 goto err
echo Test 12 passed

rem Распаковка 1 байта
%PROGRAM% unpack testing/packing6.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/unpacking6.txt
if ERRORLEVEL 1 goto err
echo Test 13 passed

%PROGRAM% pack testing/unpacking7.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/packing7.txt
if ERRORLEVEL 1 goto err
echo Test 14 passed

%PROGRAM% unpack testing/packing7.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/unpacking7.txt
if ERRORLEVEL 1 goto err
echo Test 15 passed

echo All tests passed
exit  0

:err
echo Program testing failed
exit  1