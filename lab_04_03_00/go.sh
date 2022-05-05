#!/bin/bash

./build_gcov.sh
cd func_tests/scripts/ || exit 
./func_tests.sh &> /dev/null
cd ../../
./collect_coverage.sh 
