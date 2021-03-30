#!/bin/bash

rm -rf bin
mkdir -p bin
mkdir -p bin
cc -g msqutils/msq.c structure.c main.c libs/stb_vorbis.c -o bin/daw -lm

