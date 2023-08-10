#!/bin/bash

# Check if the script has been given the correct number of arguments
if [ $# -ne 2 ]; then
  echo "Usage: $0 <channel> <n>"
  exit 1
fi

# Get the channel and the value of "n" from the command line arguments
channel="$1"
n="$2"

# Loop from 1 to "n"
for ((i=1; i<=n; i++)); do
  # Set the attribute using the iio_attr command, with the specified channel
  iio_attr -u ip:10.76.84.239 -c iio:device0 $channel raw $i
  # Sleep for 1 second
  sleep 1
done

echo "Done!"
