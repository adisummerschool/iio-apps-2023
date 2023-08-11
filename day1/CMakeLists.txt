project(iio_apps)

add_executable(hello hello.c)
add_executable(hello_iio hello_iio.c)
add_executable(ctx_attr ctx_attr.c)
add_executable(read_temp read_temp.c)
add_executable(read_chann_context read_chann_context.c)

target_link_libraries(hello_iio iio)
target_link_libraries(ctx_attr iio)
target_link_libraries(read_temp  iio)
target_link_libraries(read_chann_context iio)
