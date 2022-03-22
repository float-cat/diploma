#!/bin/bash

clear
gcc biginteger.cpp -c -DOBJ_FILE -o bigint.o -lstdc++ -lm
gcc bigint.o autotest.cpp -o autotest -lstdc++
gcc bigint.o criptotest.cpp -o criptotest -lstdc++
rm bigint.o
