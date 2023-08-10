#!/bin/bash

for i in {0..5} 
do

 iio_attr -u ip:10.76.84.205 -c ad5592r_s voltage$i raw $(( ( RANDOM % 1000 )  + 1 ))

done