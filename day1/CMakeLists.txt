project(iio_apps)

add_executable(hello hello.c)
add_executable(hello_iio hello_iio.c)
add_executable(ctx_attr ctx_attr.c)
add_executable(xadc_temp xadc_temp.c)
add_executable(read_adc read_adc.c)
add_executable(read_accel read_accel.c)

target_link_libraries(hello iio)
target_link_libraries(hello_iio iio)
target_link_libraries(ctx_attr iio)
target_link_libraries(xadc_temp iio)
target_link_libraries(read_adc iio)
target_link_libraries(read_accel iio)

