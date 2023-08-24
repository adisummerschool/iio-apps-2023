#! /usr/bin/bash
for((i=0; i<=5;i++)); do
   iio_attr -u ip:10.76.84.158 -c iio:device0 "voltage$i" raw "$i"
done
