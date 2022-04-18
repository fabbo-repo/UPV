#!/bin/bash
gcc -m32 -no-pie -fomit-frame-pointer -fno-stack-protector $1 -o $2
