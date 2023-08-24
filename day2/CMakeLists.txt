project(iio_apps)
set (CMAKE_BUILD_TYPE Debug)

add_executable(read_adc read_adc.c)
add_executable(read_accel read_accel.c)
add_executable(calib_acc calib_acc.c)
add_executable(shock_detection shock_detection.c)

target_link_libraries(read_adc iio)
target_link_libraries(read_accel iio)
target_link_libraries(shock_detection iio)
target_link_libraries(calib_acc iio)
