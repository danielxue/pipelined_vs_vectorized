#!/bin/bash

#selectivities=(0 1 10 25 50 75 90 99 100)
selectivities=( "$@" )
for s in "${selectivities[@]}"; do
  echo "s=$s"
  ./scripts/test.sh -i data/data.txt -n 10 -s "$s" -r 10 -o "logs/o${s}.txt" -l "logs/l${s}.txt"
done
