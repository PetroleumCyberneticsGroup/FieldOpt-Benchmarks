#!/bin/bash

g++ -c -pipe -g -Wall -W -D_REENTRANT -fPIE -DQT_CORE_LIB -I../WellIndexBenchmark -I. -I/opt/Qt/5.4/gcc_64/include -I/opt/Qt/5.4/gcc_64/include/QtCore -I. -I/opt/Qt/5.4/gcc_64/mkspecs/linux-g++ -o main.o ../WellIndexBenchmark/main.cpp
g++ -c -pipe -g -Wall -W -D_REENTRANT -fPIE -DQT_CORE_LIB -I../WellIndexBenchmark -I. -I/opt/Qt/5.4/gcc_64/include -I/opt/Qt/5.4/gcc_64/include/QtCore -I. -I/opt/Qt/5.4/gcc_64/mkspecs/linux-g++ -o file_handling.o ../WellIndexBenchmark/src/file_handling.cpp
g++ -c -pipe -g -Wall -W -D_REENTRANT -fPIE -DQT_CORE_LIB -I../WellIndexBenchmark -I. -I/opt/Qt/5.4/gcc_64/include -I/opt/Qt/5.4/gcc_64/include/QtCore -I. -I/opt/Qt/5.4/gcc_64/mkspecs/linux-g++ -o well_data_pcg.o ../WellIndexBenchmark/src/well_data_pcg.cpp
g++ -c -pipe -g -Wall -W -D_REENTRANT -fPIE -DQT_CORE_LIB -I../WellIndexBenchmark -I. -I/opt/Qt/5.4/gcc_64/include -I/opt/Qt/5.4/gcc_64/include/QtCore -I. -I/opt/Qt/5.4/gcc_64/mkspecs/linux-g++ -o test_wells.o ../WellIndexBenchmark/src/test_wells.cpp
g++ -c -pipe -g -Wall -W -D_REENTRANT -fPIE -DQT_CORE_LIB -I../WellIndexBenchmark -I. -I/opt/Qt/5.4/gcc_64/include -I/opt/Qt/5.4/gcc_64/include/QtCore -I. -I/opt/Qt/5.4/gcc_64/mkspecs/linux-g++ -o well_rms.o ../WellIndexBenchmark/src/well_rms.cpp
g++ -c -pipe -g -Wall -W -D_REENTRANT -fPIE -DQT_CORE_LIB -I../WellIndexBenchmark -I. -I/opt/Qt/5.4/gcc_64/include -I/opt/Qt/5.4/gcc_64/include/QtCore -I. -I/opt/Qt/5.4/gcc_64/mkspecs/linux-g++ -o well_pcg.o ../WellIndexBenchmark/src/well_pcg.cpp
g++ -Wl,-rpath,/opt/Qt/5.4/gcc_64 -Wl,-rpath,/opt/Qt/5.4/gcc_64/lib -o WellIndexBenchmark main.o file_handling.o well_data_pcg.o test_wells.o well_rms.o well_pcg.o   -L/opt/Qt/5.4/gcc_64/lib -lQt5Core -lpthread 



