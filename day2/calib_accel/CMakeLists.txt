project(calib_accel)

add_executable(calib_accel calib_accel.c)

target_link_libraries(calib_accel iio)
