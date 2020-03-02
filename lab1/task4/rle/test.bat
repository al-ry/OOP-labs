set PROGRAM="%~1"

%PROGRAM% invalidArguments 
if NOT ERRORLEVEL 1 goto err

%PROGRAM% packMode testing/empty.txt %TEMP%\out.txt 
if NOT ERRORLEVEL 1 goto err

%PROGRAM% pack invalid.txt %TEMP%\out.txt 
if NOT ERRORLEVEL 1 goto err

%PROGRAM% pack testing/empty.txt out.txt
if NOT ERRORLEVEL 1 goto err

%PROGRAM% pack testing/empty.txt %TEMP%\out.txt 
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/empty.txt
if ERRORLEVEL 1 goto err
echo Test 1 passed

%PROGRAM% pack testing/unpacking1.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/packing1.txt
if ERRORLEVEL 1 goto err
echo Test 2 passed

%PROGRAM% unpack testing/packing1.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/unpacking1.txt
if ERRORLEVEL 1 goto err
echo Test 3 passed

%PROGRAM% pack testing/unpacking2.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/packing2.txt
if ERRORLEVEL 1 goto err
echo Test 4 passed

%PROGRAM% unpack testing/packing2.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/unpacking2.txt
if ERRORLEVEL 1 goto err
echo Test 5 passed

%PROGRAM% pack testing/unpacking3.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt testing/packing3.txt
if ERRORLEVEL 1 goto err
echo Test 6 passed

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


echo All tests passed
exit  0

:err
echo Program testing failed
exit  1