project(iio_apps)

add_executable(hello_iio_1 hello_iio.c)
add_executable(ctx_attr ctx_attr.c)
add_executable(text_context text_context.c)
add_executable(read_all_chanels read_all_chanels.c)
add_executable(read_temp read_temp.c)

target_link_libraries(hello_iio_1 iio)
target_link_libraries(text_context iio)
target_link_libraries(ctx_attr iio)
target_link_libraries(read_all_chanels iio)
target_link_libraries(read_temp iio)
