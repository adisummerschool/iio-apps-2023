#!/bin/bash
n=$1
chan=0
for i in $(seq 1 $n); do
for chan in $(seq 0 5); do
  echo "Channel ${chan}: "
  iio_attr -u ip:10.76.84.239 -c iio:device0 voltage${chan} raw $chan
done
  sleep 1
done