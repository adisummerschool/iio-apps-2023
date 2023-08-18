project(shock_detect)

add_executable(shock_detect shock_detect.c)

target_link_libraries(shock_detect iio)
