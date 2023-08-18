project(iio_apps)
set (CMAKE_BUILD_TYPE Debug)

add_executable(read_adc read_adc.c)
add_executable(read_accel read_accel.c)

target_link_libraries(read_adc iio)
target_link_libraries(read_accel iio)
