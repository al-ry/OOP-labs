
set PROGRAM="%~1"

rem При запуске без параметров ожидается ненулевой код возврата

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

rem Передаем несколько аргументов

%PROGRAM% 20 20 > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\more_arguments.txt
if ERRORLEVEL 1 goto err
echo Test 2 passed

rem Передаем буквы, а не число
%PROGRAM% cat > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\letters_argument.txt
if ERRORLEVEL 1 goto err
echo Test 3 passed

%PROGRAM% 23abc > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\letters_argument.txt
if ERRORLEVEL 1 goto err
echo Test 4 passed

%PROGRAM% -23abc > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\letters_argument.txt
if ERRORLEVEL 1 goto err
echo Test 5 passed

rem Граничное значение
%PROGRAM% 255 > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\edge_value_255.txt
if ERRORLEVEL 1 goto err
echo Test 6 passed

rem Граничное значение
%PROGRAM% 0 > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\edge_value_0.txt
if ERRORLEVEL 1 goto err
echo Test 7 passed

rem Реверс байтов в числе 6
%PROGRAM% 6 > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\flip_6.txt
if ERRORLEVEL 1 goto err
echo Test 8 passed

echo All tests passed
exit  0

:err
echo Program testing failed
exit  1