:: ---------------------------------------------------------------------
:: COMPILERS COURSE - SCRIPT                                           -
:: SCRIPT A22 - CST8152 - Fall 2023                                    -
:: ---------------------------------------------------------------------

CLS
SET COMPILER=Compiler.exe

SET FILE1=INPUT0_Empty
SET FILE2=INPUT1_Hello
SET FILE3=INPUT2_Volume
SET FILE4=INPUT3_Factorial
SET FILE5=INPUT4_Datatypes
SET FILE6=INPUT5_General
SET FILE7=INPUT6_Big

SET ASSIGNMENT=A32
SET EXTENSION=gos
SET OUTPUT=out
SET ERROR=err

SET PARAM=p

:: ---------------------------------------------------------------------
:: Begin of Tests (A22 - F23) ------------------------------------------
:: ---------------------------------------------------------------------

@echo off

ECHO "=---------------------------------------="
ECHO "|  COMPILERS - ALGONQUIN COLLEGE (F23)  |"
ECHO "=---------------------------------------="
echo "                    (((((((((((((,          .((((((((((((("
echo "                ,(((((((((((((((((((     (((((((((((((((((((("
echo "(((((((((*  ./((((((((/ ((((((((((*  ,(((((((((("
echo "                ((((((((                ,(((((((           (((((((."
echo "            (((((((.     (((((((((((((((((((             ((((((("
echo "    .,,,,,,*   (((((((     (((((((((((((((((((*            ,((((((*"
echo "            ((((((((          ((((((((((((((           (((((((("
echo "                (((((((((,    ((((((((( ((((((((((     (((((((((/"
echo "                ((((((((((((((((((((     ((((((((((((((((((((,"
echo "                    ((((((((((((((          ,(((((((((((((("
ECHO "=---------------------------------------="
ECHO "                                   "
ECHO "[READER SCRIPT .........................]"
ECHO "                                   "

ren *.exe %COMPILER%

::
:: BASIC TESTS  ----------------------------------------------------------
::
:: Basic Tests (A22 - F23) - - - - - - - - - - - - - - - - - - - - - -

::
:: BASIC TESTS  ----------------------------------------------------------
::
:: Basic Tests (A22 - F23) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% %PARAM% %FILE1%.%EXTENSION%	> %FILE1%-%ASSIGNMENT%.%OUTPUT%	2> %FILE1%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE2%.%EXTENSION%	> %FILE2%-%ASSIGNMENT%.%OUTPUT%	2> %FILE2%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE3%.%EXTENSION%	> %FILE3%-%ASSIGNMENT%.%OUTPUT%	2> %FILE3%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE4%.%EXTENSION%	> %FILE4%-%ASSIGNMENT%.%OUTPUT%	2> %FILE4%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE5%.%EXTENSION%	> %FILE5%-%ASSIGNMENT%.%OUTPUT%	2> %FILE5%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE6%.%EXTENSION%	> %FILE6%-%ASSIGNMENT%.%OUTPUT%	2> %FILE6%-%ASSIGNMENT%.%ERROR%

:: SHOW OUTPUTS - - - - - - - - - - - - - - - - - - - - - - - - - - -
DIR *.OUT
DIR *.ERR

:: ---------------------------------------------------------------------
:: End of Tests (A22 - F23) --------------------------------------------
:: ---------------------------------------------------------------------
