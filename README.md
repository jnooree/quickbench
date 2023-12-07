# quickbench

## Introduction

This repository contains a collection of quick, informal C++ benchmarks
primarily for my personal reference. Feel free to use them if you find them
beneficial.

## Building

First, set up the Google Benchmark library. This step requires cmake and a C++
compiler with C++11 support.

```bash
./bootstrap.sh
```

Next, compile the benchmarks. This process requires GNU parallel and `g++`.

```bash
./build.sh [files...]
```

If no files are specified, all benchmarks will be compiled. All benchmarks will
be generated as executables in the `bin` directory.

## Running

Refer to the [google benchmark](https://github.com/google/benchmark)
documentation for detailed instructions on how to run the benchmarks.

## License

This work is released under the Public Domain or CC0, whichever is more
permissive, unless otherwise specified in each file.

**DISCLAIMER:** This licensing policy is intended to make this repository as
permissive as possible. However, I have not verified that all the code is
actually eligible for Public Domain or CC0. There may be instances where
copyrighted code has been inadvertently included in this repository. In such
cases, the license of the original code applies. Please refer to each file for
possible license information.

If you find any license violations, please let me know and I will fix them.
