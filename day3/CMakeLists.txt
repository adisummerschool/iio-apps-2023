project(iio_apps_3)

add_executable(shock_buffer shock_buffer.c)

target_link_libraries(shock_buffer iio)
