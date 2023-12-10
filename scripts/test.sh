#!/bin/bash

output_file=/dev/stdout
perf_logs=/dev/null

while getopts i:o:l:n:s:r: option
do
  case "${option}"
    in
    i)input_data=${OPTARG};;
    o)output_file=${OPTARG};;
    l)perf_logs=${OPTARG};;
    n)num_terms=${OPTARG};;
    s)selectivity=${OPTARG};;
    r)num_runs=${OPTARG};;
    ?)exit 1
  esac
done

# clear output files
true > "$output_file"
true > "$perf_logs"

# setup perf control
ctl_dir=/tmp/

ctl_fifo=${ctl_dir}perf_ctl.fifo
test -p ${ctl_fifo} && unlink ${ctl_fifo}
mkfifo ${ctl_fifo}
exec {ctl_fd}<>${ctl_fifo}

# benchmark
{ echo "$*"; echo "runtime (ns)"; } >> "$output_file"
echo -e "pipelined\tvectorized\tvectorized no simd" >> "$output_file"

predicate="A < $selectivity"
for ((i=1; i <= num_terms; i++)); do
  ./scripts/build.sh -f "$input_data" -t "int32_t" -p "$predicate" &> /dev/null

  pipelined_time=0
  for _ in $(seq "$num_runs"); do
    pipelined_time=$((pipelined_time + $(./build/pipelined_executor)))
  done
  pipelined_time=$((pipelined_time / num_runs))

  vectorized_time=0
  for _ in $(seq "$num_runs"); do
    vectorized_time=$((vectorized_time + $(./build/vectorized_executor)))
  done
  vectorized_time=$((vectorized_time / num_runs))

  vectorized_no_simd_time=0
  for _ in $(seq "$num_runs"); do
    vectorized_no_simd_time=$((vectorized_no_simd_time + $(./build/vectorized_executor_no_simd)))
  done
  vectorized_no_simd_time=$((vectorized_no_simd_time / num_runs))

  echo -e "$pipelined_time\t$vectorized_time\t$vectorized_no_simd_time" >> "$output_file"

  echo "number of predicates: $i; pipelined" >> "$perf_logs"
  perf stat -e "branch-misses,branch-instructions,cache-misses,cache-references,instructions,cpu-cycles" \
    -x "\t" --append -o "$perf_logs" \
    --delay=-1 --control fd:$ctl_fd \
    -- ./build/pipelined_executor --control $ctl_fd --disable-time &> /dev/null
  echo "" >> "$perf_logs"

  echo "number of predicates: $i; vectorized" >> "$perf_logs"
  perf stat -e "branch-misses,branch-instructions,cache-misses,cache-references,instructions,cpu-cycles" \
    -x "\t" --append -o "$perf_logs" \
    --delay=-1 --control fd:$ctl_fd \
    -- ./build/vectorized_executor --control $ctl_fd --disable-time &> /dev/null
  echo "" >> "$perf_logs"

  echo "number of predicates: $i; vectorized no simd" >> "$perf_logs"
  perf stat -e "branch-misses,branch-instructions,cache-misses,cache-references,instructions,cpu-cycles" \
    -x "\t" --append -o "$perf_logs" \
    --delay=-1 --control fd:$ctl_fd \
    -- ./build/vectorized_executor_no_simd --control $ctl_fd --disable-time &> /dev/null
  echo "" >> "$perf_logs"

  predicate+=" AND $(printf "\x$(printf %x $((i + 65)))") < $selectivity"
done
