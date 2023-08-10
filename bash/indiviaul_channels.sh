#!/bin/bash

for i in {0..5}; do
    f_name="voltage$i"
    # echo $f_name
    iio_attr -u "ip:10.76.84.215" -c ad5592r_s $f_name raw $i
done