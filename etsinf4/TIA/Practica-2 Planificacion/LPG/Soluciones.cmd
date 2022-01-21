@echo off
title Ejecutar LPG
set/p file1= Cual es el primer fichero? (dominio) 
set/p file2= Cual es el segundo fichero? (problema) 
set/p soluciones= Cuantas soluciones? 
echo Ejecutando lpg-td.exe -o %file1% -f %file2% -n %soluciones%
lpg-td.exe -o %file1% -f %file2% -n %soluciones%
pause
exit