#!/bin/bash

for i in $(seq 1 10);
do
    iio_attr -u ip:10.76.84.205 -c ad5592r_s voltage3 raw $i
    sleep 1
done

