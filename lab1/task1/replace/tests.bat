set PROGRAM="%~1"


%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% tests-data/input1.txt %TEMP%\out.txt "" "replace"
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

%PROGRAM% tests-data/input2.txt %TEMP%\out.txt "*" " "
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests-data/output2.txt
if ERRORLEVEL 1 goto err
echo Test 2 passed

%PROGRAM% tests-data/input3.txt %TEMP%\out.txt "ma" "mama"
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests-data/output3.txt
if ERRORLEVEL 1 goto err
echo Test 3 passed


%PROGRAM% tests-data/input4.txt %TEMP%\out.txt "1231234" " "
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests-data/output4.txt
if ERRORLEVEL 1 goto err
echo Test 4 passed

%PROGRAM% tests-data/input5.txt %TEMP%\out.txt "dog" "cat"
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests-data/output5.txt
if ERRORLEVEL 1 goto err
echo Test 5 passed


%PROGRAM% tests-data/input6.txt %TEMP%\out.txt "replace it" "!"
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests-data/output6.txt
if ERRORLEVEL 1 goto err
echo Test 6 passed

%PROGRAM% tests-data/input7.txt %TEMP%\out.txt "123" "q"
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests-data/output7.txt
if ERRORLEVEL 1 goto err
echo Test 7 passed

%PROGRAM% tests-data/input8.txt %TEMP%\out.txt "empty" "file"
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests-data/output8.txt
if ERRORLEVEL 1 goto err
echo Test 8 passed


echo All tests passed
exit  0

:err
echo Program testing failed
exit  1
