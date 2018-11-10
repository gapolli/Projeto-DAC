#!/bin/bash
rm -rf projeto-dac.exe
gcc -c *.c
gcc *.o -o projeto-dac.exe
./projeto-dac.exe
