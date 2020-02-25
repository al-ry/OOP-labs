set PROGRAM="%~1"


%PROGRAM% testing/matrix1.txt > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt  testing/matrix1_out.txt
if ERRORLEVEL 1 goto err
echo Test 1 passed

%PROGRAM% testing/matrix2.txt > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt  testing/matrix2_out.txt
if ERRORLEVEL 1 goto err
echo Test 2 passed

%PROGRAM% testing/matrix3.txt > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt  testing/matrix3_out.txt
if ERRORLEVEL 1 goto err
echo Test 3 passed

%PROGRAM% testing/matrix4.txt > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt  testing/matrix4_out.txt
if ERRORLEVEL 1 goto err
echo Test 4 passed

%PROGRAM% testing/unit_matrix.txt > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt  testing/unit_matrix_out.txt
if ERRORLEVEL 1 goto err
echo Test 5 passed

%PROGRAM% testing/zero_deteminant1.txt > %TEMP%\out.txt
fc %TEMP%\out.txt  testing/zero_deteminant1_out.txt
if ERRORLEVEL 1 goto err
echo Test 6 passed

%PROGRAM% testing/zero_deteminant2.txt > %TEMP%\out.txt
fc %TEMP%\out.txt  testing/zero_deteminant2_out.txt
if ERRORLEVEL 1 goto err
echo Test7 passed

%PROGRAM% testing/2x2matrix_err.txt > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err
echo Test8 passed

echo All tests passed
exit  0

:err
echo Program testing failed
exit  1