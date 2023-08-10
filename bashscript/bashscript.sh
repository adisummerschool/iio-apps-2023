#!/bin/bash

n=$1
can=0
for i in $(seq 1 $n)
do
for can in $(seq 0 5)
do
  echo "writting to channel ${can}: "
  iio_attr -u ip:10.76.84.128 -c iio:device0 voltage${can} raw $can
done
  sleep 1
done
