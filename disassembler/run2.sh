#!/bin/bash

gcc diasm.c -o chip8-dump
./chip8-dump ../roms/Tetris.ch8
