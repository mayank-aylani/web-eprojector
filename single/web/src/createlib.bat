g++ -c webearl.cpp -I ..\include
ar rcs webearl.lib *.o
del ..\lib\webearl.lib
move webearl.lib ..\lib