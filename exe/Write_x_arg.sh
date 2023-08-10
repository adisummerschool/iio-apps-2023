#!/bin/bash
ip=$1
n=$2
chan=0
for chan in $(seq 0 5)
do
if [ $chan -eq $n ]
then
echo "Writing to channel${chan}: "
iio_attr -u ip:10.76.84.199 -c ad5592r_s voltage${chan} raw $(($chan))
fi
done
sleep 1