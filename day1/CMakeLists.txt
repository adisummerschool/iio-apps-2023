project(iio_apps)

add_executable(hello hello.c)

add_executable(hello_iio hello_iio.c)
target_link_libraries(hello_iio iio)

add_executable(ctx_attr ctx_attr.c)
target_link_libraries(ctx_attr iio)

add_executable(read_temp read_temp.c)
target_link_libraries(read_temp iio)

add_executable(01-context-error 01-context-error.c)
target_link_libraries(01-context-error iio)

add_executable(02-read-ctx-attr 02-read-ctx-attr.c)
target_link_libraries(02-read-ctx-attr iio)

add_executable(03-read-dev-chan 03-read-dev-chan.c)
target_link_libraries(03-read-dev-chan iio)


add_executable(04-xadc-temp 04-xadc-temp.c)
target_link_libraries(04-xadc-temp iio)
