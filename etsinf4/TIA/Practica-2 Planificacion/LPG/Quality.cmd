@echo off
title Ejecutar LPG
set/p file1= Cual es el primer fichero? (dominio) 
set/p file2= Cual es el segundo fichero? (problema) 
echo Ejecutando lpg-td.exe -o %file1% -f %file2% -quality
lpg-td.exe -o %file1% -f %file2% -quality
pause
exit