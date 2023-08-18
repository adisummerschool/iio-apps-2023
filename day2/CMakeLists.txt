project(iio_apps)

add_executable(axes axes.c)

target_link_libraries(axes iio)
