#!/bin/bash

# Loop from 0 to 5
for i in {0..5}; do
  # Create the channel name "voltageX" where X is the current value of i
  channel="voltage$i"

  # Set the attribute using the iio_attr command with the created channel name
  iio_attr -u ip:10.76.84.239 -c iio:device0 $channel raw $i

  # Optional: print a message indicating the command has been run
  echo "Set $channel to $i"
done

echo "Done!"
