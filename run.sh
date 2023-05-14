#!/bin/bash
make
rm result.txt
./test.out >> result.txt
