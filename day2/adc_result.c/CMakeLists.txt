project(iio_apps_2)

add_executable(adc_res adc_result.c)
add_executable(shock shock_detect.c)
add_executable(buf read_buf.c)

target_link_libraries(buf iio)
target_link_libraries(shock iio)
target_link_libraries(adc_res iio)
