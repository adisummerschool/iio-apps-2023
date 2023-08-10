#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Usage: $channel> <n>"
	exit 1
fi

channel="$1"
n="$2"

for ((i = 1; i <= n; i++)); do 
	iio_attr -u ip:10.76.84.239 -c iio:device0 $channel raw $i
	sleep 1
done
echo "DONE"
