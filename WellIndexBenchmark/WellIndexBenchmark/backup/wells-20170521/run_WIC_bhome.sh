#!/bin/bash

RUN="build-WellIndexBenchmark-Desktop_Qt_5_4_1_GCC_64bit-Debug"
LIB="../../build-FieldOpt-old-Desktop_Qt_5_4_1_GCC_64bit-Debug/"; \
LD_LIBRARY_PATH=${LIB}"/ERTWrapper":${LIB}"/WellIndexCalculator":${LIB}"/Utilities":${LIB}"/Model" \
../../${RUN}/wellindexbenchmark all