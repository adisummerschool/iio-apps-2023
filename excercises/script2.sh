#!/bin/sh

for i in {0..5}; do
#Create the channel name "voltageX" where  X is the current value of i
	
#Set the attribute using the iio_attr command with the createdd channel name
iio_attr -u ip:10.76.84.239 -c ad5592r_s voltage$i raw $i
#Print the message indicating the command has been run 
	echo "Set $channel to $i"
done

echo  "Done!"

