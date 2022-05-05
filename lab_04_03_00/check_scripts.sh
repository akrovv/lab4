#!/bin/bash


shellcheck ./*.sh
shellcheck func_tests/scripts/*.sh

echo "Критических ошибок найдено не было."