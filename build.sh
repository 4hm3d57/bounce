#!/bin/bash

set -e


echo "Compiling bounce project..."

g++ src/*.cpp src/glad.c -Iinclude -o bounce -lglfw -ldl -lGL

echo "Build successfull!"
