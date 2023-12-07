#!/bin/bash

shopt -s nullglob

mkdir -p bin

mapfile -t flags <compile_flags.txt

declare -a files
if [[ $# -eq 0 ]]; then
	files=(src/*.cpp)
else
	files=("$@")
fi

parallel -t g++ -Ofast -g "${flags[@]}" -o 'bin/{/.}' '{}' \
	-Llib -lbenchmark -lbenchmark_main -lpthread ::: "${files[@]}"
