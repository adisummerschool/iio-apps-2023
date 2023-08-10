#!/bin/bash

#iio_info -u ip:10.76.84.158

echo "Enter value for n"
read n

sleep 1

for (( i=0; i<=$n; i++ ))
do
   iio_attr -u ip:10.76.84.158 -c iio:device0 voltage0 raw $i
   sleep 1
done

sleep 2

for (( i=0; i<=5; i++ ))
do
   iio_attr -u ip:10.76.84.158 -c iio:device0 voltage$i raw $i
   sleep 1
done

#var = `iio_attr -u ip:10.76.84.158 -c iio:device0 voltage1 raw`

#echo "Value: $var"
