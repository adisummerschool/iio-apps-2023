project(iio_apps)

add_executable(hello hello.c)
add_executable(ctx_attr ctx_attr.c)
target_link_libraries(hello iio)
target_link_libraries(ctx_attr iio)
