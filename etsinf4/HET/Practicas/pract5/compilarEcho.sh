#!/bin/sh
gcc -ggdb -m32 -fno-stack-protector -fno-pie -no-pie echo.c -o echo
