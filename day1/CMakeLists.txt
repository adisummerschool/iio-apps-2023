cmake_minimum_required(VERSION 3.26.4)

project(iio_apps)

add_executable(hello hello.c)
add_executable(ctx_attr ctx_attr.c)
add_executable(read_temp read_temp.c)

target_link_libraries(hello iio)
target_link_libraries(ctx_attr iio)
target_link_libraries(read_temp iio)

