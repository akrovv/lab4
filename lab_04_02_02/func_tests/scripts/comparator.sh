#!/bin/bash

str1="$(grep < "$1" -oP '(?<=Result:)[[:space:]]*([[:alpha:]][[:alpha:]]*|[[:digit:]][[:digit:]]*)[[:space:]](yes|no)' | sed 's/ //g')"
str2="$(grep < "$2" -oP '(?<=Result:)[[:space:]]*([[:alpha:]][[:alpha:]]*|[[:digit:]][[:digit:]]*)[[:space:]](yes|no)' | sed 's/ //g')"

if [[ -z "$str1" ]] && [[ -z "$str2" ]]; then
  exit 1
fi
if [ -n "$str1" ] && [ -n "$str2" ]; then
  if test "$str1" = "$str2"; then
    exit 0
  else
    exit 1
  fi
fi 
exit 1