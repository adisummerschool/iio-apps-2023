#!/bin/bash

n=5  # Replace this with the desired value

  for ((i = 0; i <= $n; i++)); do
    
    iio_attr -u ip:10.76.84.158 -c iio:device0 voltage$i raw $i

    sleep 1

    done