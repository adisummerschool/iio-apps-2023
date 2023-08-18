project(iio_apps)

add_executable(hello hello.c)
add_executable(hello_iio hello_iio.c)
add_executable(ctx_attr ctx_attr.c)
add_executable(task1 task1.c)
add_executable(read_temp read_temp.c)
add_executable(get_channels get_channels.c)
add_executable(read_adxl read_adxl.c)
add_executable(read_bucla read_bucla.c)




target_link_libraries(hello_iio iio)
target_link_libraries(ctx_attr iio)
target_link_libraries(task1 iio)
target_link_libraries(read_temp iio)
target_link_libraries(get_channels iio)
target_link_libraries(read_adxl iio)
target_link_libraries(read_bucla iio)




