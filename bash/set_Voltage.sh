for i in {0..5}; do

#set the attribute 
	iio_attr -u ip:10.76.84.239 -c ad5592r_s voltage$i raw $i
	echo "Set channel to $i"
done 
echo "DONE"
