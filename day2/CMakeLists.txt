project(iio_apps)

add_executable(calib_accel calib_accel.c)
add_executable(read_accel read_accel.c)
add_executable(read_adc read_adc.c)
add_executable(shock_detect shock_detect.c)


target_link_libraries(calib_accel iio)
target_link_libraries(read_accel iio)
target_link_libraries(read_adc iio)
target_link_libraries(shock_detect iio)
