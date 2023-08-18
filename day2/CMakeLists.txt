project(iio_apps)

add_executable(read_xyz read_xyz.c)
add_executable(read_accel read_accel.c)
add_executable(calib_accel calib_accel.c)
add_executable(shock_detect shock_detect.c)

target_link_libraries(read_xyz iio)
target_link_libraries(read_accel iio)
target_link_libraries(calib_accel iio)
target_link_libraries(shock_detect iio)
