#!/bin/bash

file_stream_in="${1}"
file_app_args=""

if [ $# -gt 1 ]; then
  file_app_args=$(cat "${3}")
fi

if [ -n "$USE_VALGRIND" ]; then
  eval "valgrind --log-file=valgrind_out.txt -q ../../app.exe < $file_stream_in > ./program_out.txt $file_app_args"
else
  eval "../../app.exe < $file_stream_in > ./program_out.txt $file_app_args"
fi

if test $? -ne 0; then
  exit 0
else
  exit 1
fi