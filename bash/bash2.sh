#!/bin/bash


for i in $(seq 1 5);
do
    iio_attr -u ip:10.76.84.244 -c ad5592r_s voltage$i raw $i
done

echo After...
sleep 2
for i in $(seq 1 5);
do
    iio_attr -u ip:10.76.84.244 -c ad5592r_s voltage$i
done