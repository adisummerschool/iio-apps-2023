#!/bin/bash

#Loop from 0 to 5 -> 6 channels
for i in {0..5}; do
	#Create channel "voltageX" where X is the value of i
	channel="voltage$i"
	#Set the attribute using the iio_atr command with the channel name
	iio_attr -u ip:10.76.84.239 -c iio:device0 $channel raw $i
	echo "Set $channel to $i"
done
echo "Done!"
