cmake_minimum_required(VERSION 3.26.4)

project(iio_apps)

add_executable(challenge1 Challenge1.c)
add_executable(challenge3 Challenge3.c)
# add_executable(challenge4 Challenge4.c)
add_executable(challenge5 Challenge5.c)

target_link_libraries(challenge1 iio)
target_link_libraries(challenge3 iio)
# target_link_libraries(challenge4 iio)
target_link_libraries(challenge5 iio)
