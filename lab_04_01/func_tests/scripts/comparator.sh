#!/bin/bash

float_f="$(grep < "$1" -oE '[[:space:]]*\-?[0-9][0-9]*\.[0-9][0-9]*' | sed 's/ //g')"
int_f="$(grep < "$1" -oE '^[[:alpha:]][[:punct:]][[:space:]]*\-?[[0-9][0-9]*|[[:space:]][[:space:]]*\-?[[0-9][0-9]*|[^[:alpha:][:punct:][:space:]]*\-?[[0-9][0-9]*' | sed 's/ //g')"
float_s="$(grep < "$2" -oE '[[:space:]]*\-?[0-9][0-9]*\.[0-9][0-9]*$' | sed 's/ //g')"
int_s="$(grep < "$2" -oE '^[[:alpha:]][[:punct:]][[:space:]]*\-?[[0-9][0-9]*|[[:space:]][[:space:]]*\-?[[0-9][0-9]*|[^[:alpha:][:punct:][:space:]]*\-?[[0-9][0-9]*' | sed 's/ //g')"

if [[ -z "$float_f" ]] && [[ -z "$int_f" ]] && [[ -z "$float_s" ]] && [[ -z "$int_s" ]]; then
  exit 1
fi
if [ -n "$float_f" ] && [ -n "$float_s" ]; then
  if test "$float_f" = "$float_s"; then
    exit 0
  else
    exit 1
  fi
elif [ -n "$int_f" ] && [ -n "$int_s" ]; then
  if test "$int_f" = "$int_s"; then
    exit 0
  else 
    exit 1
  fi
fi 
exit 1
