project(iio_apps)

add_executable(hello hello.c)
target_link_libraries(hello iio)

add_executable(hello_iio hello_iio.c)
target_link_libraries(hello_iio iio)

add_executable(ctx_attr ctx_attr.c)
target_link_libraries(ctx_attr iio)

add_executable(read_temp read_temp.c)
target_link_libraries(read_temp iio) 

add_executable(dev-chan_attr dev-chan_attr.c)
target_link_libraries(dev-chan_attr iio)