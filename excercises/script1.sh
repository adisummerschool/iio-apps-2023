#!/bin/sh

for i in $(seq 0 5); do
  channel="voltage$i"
  iio_attr -u ip:10.76.84.128 -c ad5592r_s $channel raw $i
  echo "Set $channel to $i"
done
echo "Done!"
