project(read_xyz)

add_executable(read_xyz read_xyz.c)

target_link_libraries(read_xyz iio)
