project(read_accel)

add_executable(read_accel read_accel.c)

target_link_libraries(read_accel iio)
