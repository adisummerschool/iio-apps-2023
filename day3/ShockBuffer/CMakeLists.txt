project(iio_apps)
set (CMAKE_BUILD_TYPE Debug)

add_executable(shock_buffer shock_buffer.c)

target_link_libraries(shock_buffer iio)