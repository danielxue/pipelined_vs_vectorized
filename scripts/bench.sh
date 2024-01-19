p7_time=0
for _ in {1..10}; do
  p7_time=$((p7_time + $(./build/vectorized_executor_no_simd_s50_p7)))
done
p7_time=$((p7_time / 10))
echo "p7: ${p7_time}"

p8_time=0
for _ in {1..10}; do
  p8_time=$((p8_time + $(./build/vectorized_executor_no_simd_s50_p8)))
done
p8_time=$((p8_time / 10))
echo "p8: ${p8_time}"
