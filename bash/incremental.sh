#!/bin/bash

# Check if exactly one argument is provided
if [ "$#" -ne 1 ]; then
  echo "run using: $0 <argument>"
  exit 1
fi

n_iterations="$1"

# Rest of your code here
echo "You provided the following argument: $n_iterations"


for ((i = 1; i < n_iterations + 1; i++)); do
#   echo "This is iteration number $i"
  sleep 1s
  iio_attr -u "ip:10.76.84.215" -c ad5592r_s voltage1 raw $i
done
