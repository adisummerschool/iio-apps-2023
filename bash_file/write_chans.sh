    #!/bin/bash
    
    iio_attr -u ip:10.76.84.205 -c ad5592r_s voltage0 raw 1
    iio_attr -u ip:10.76.84.205 -c ad5592r_s voltage1 raw 2
    iio_attr -u ip:10.76.84.205 -c ad5592r_s voltage2 raw 3
    iio_attr -u ip:10.76.84.205 -c ad5592r_s voltage3 raw 4
    iio_attr -u ip:10.76.84.205 -c ad5592r_s voltage4 raw 5
    iio_attr -u ip:10.76.84.205 -c ad5592r_s voltage5 raw 6
    sleep 1