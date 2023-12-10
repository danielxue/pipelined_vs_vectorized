#!/bin/bash

while getopts f:t:p: option
do
  case "${option}"
    in
    f)filename=${OPTARG};;
    t)data_type=${OPTARG};;
    p)predicates=${OPTARG};;
    ?)exit 1
  esac
done

cog -d -D filename="$filename" -D data_type="$data_type" -D predicates="$predicates" src/pipelined_executor/pipelined_executor_template.cpp > src/pipelined_executor/pipelined_executor.cpp
cog -d -D filename="$filename" -D data_type="$data_type" -D predicates="$predicates" src/vectorized_executor/vectorized_executor_template.cpp > src/vectorized_executor/vectorized_executor.cpp

cmake --build build
