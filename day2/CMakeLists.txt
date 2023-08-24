project(iio_apps_2)

add_executable(day2_app day2_app.c)
add_executable(day2_app_2 day2_app_2.c)
add_executable(calib_accel calib_accel.c)
add_executable(detect_shock detect_shock.c)

target_link_libraries(day2_app iio)
target_link_libraries(day2_app_2 iio)
target_link_libraries(calib_accel iio)
target_link_libraries(detect_shock iio)