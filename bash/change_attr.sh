#!/bin/sh

IP=$1

for i in $(seq 0 5)
do
	j=$(od -An -N2 -i /dev/random)
	iio_attr -u "ip:10.76.84.$IP" -c ad5592r_s "voltage$i" raw $j
done
