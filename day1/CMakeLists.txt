project(iio_apps)

add_executable(hello hello.c)
add_executable(hello_iio hello_iio.c)
add_executable(ctx_attr ctx_attr.c)
add_executable(readtemp readtemp.c)
add_executable(read_all_channels read_all_channels.c)

target_link_libraries(hello_iio iio)
target_link_libraries(ctx_attr iio)
target_link_libraries(readtemp iio)
target_link_libraries(read_all_channels iio)