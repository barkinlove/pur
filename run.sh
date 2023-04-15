#!/bin/sh

cd build
cmake --build . --config Release 
./pur
cd ..
