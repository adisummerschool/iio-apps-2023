#!/bin/bash

for i in {0..10} 
do

 iio_attr -u ip:10.76.84.205 -c ad5592r_s voltage0 raw $i
 sleep 5

done