#! /usr/bin/bash
read -p "Enter the value of n: " n

if [[ ! "$n" =~ ^[0-9]+$ ]]; then
   echo "Invalid input. Please enter a valid number."
   exit 1
fi

for((i=1; i<=n;i++)); do
   iio_attr -u ip:10.76.84.158 -c iio:device0 voltage3 raw "$i"
   sleep 1
done
