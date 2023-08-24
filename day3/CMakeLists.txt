cmake_minimum_required(VERSION 3.26.4)

project(iio_apps)

add_executable(shock_buffer shock_buffer.c)

target_link_libraries(shock_buffer iio)
