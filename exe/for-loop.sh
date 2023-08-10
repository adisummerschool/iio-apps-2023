#!/bin/bash
n=$1
ip=10.76.84.199
chan=0
for i in $(seq 0 $n)
do
for chan in $(seq 0 5)
do
echo "Writing to channel${chan}: "
iio_attr -u ip:${ip} -c ad5592r_s voltage${chan} raw $(($i))
done
done