#!/bin/bash -e

cmake -B benchmark/build -S benchmark \
	-DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY="$(pwd)/lib" \
	-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
	-DBENCHMARK_ENABLE_INSTALL=OFF \
	-DBENCHMARK_ENABLE_GTEST_TESTS=OFF
cmake --build benchmark/build -j -t benchmark benchmark_main
