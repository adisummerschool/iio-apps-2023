project(iio_apps)

add_executable(read_buffer read_buffer.c)
target_link_libraries(read_buffer iio)
