project(iio_apps)

add_executable(hello hello.c)
add_executable(hello_iio hello_iio.c)
add_executable(ctx_attr ctx_attr.c)
add_executable(task2 task2.c) 
add_executable(task3 task3.c) 
add_executable(task4 task4.c) 

target_link_libraries(hello_iio iio)
target_link_libraries(ctx_attr iio)
target_link_libraries(task2 iio)
target_link_libraries(task3 iio)
target_link_libraries(task4 iio)