#!/bin/bash

if [ $# -ne 2 ]; then
	echo "You need to type 2 arguments!"
	exit 1
fi

channel="$1" #canalul e primul argument
n="$2" #n e al doilea

for ((i=1; i<=n; i++)); do
	iio_attr -u ip:10.76.84.239 -c iio:device0 $channel raw $i
	sleep 1
done

echo "Done!"
