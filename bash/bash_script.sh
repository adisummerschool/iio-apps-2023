#!/bin/bash
echo "Enter value for n"
   read n
   sleep 1
# Replace this with the desired value

  for ((i = 1; i <= $n; i++)); do
    
    iio_attr -u ip:10.76.84.158 -c iio:device0 voltage0 raw $i

    sleep 1

    done
