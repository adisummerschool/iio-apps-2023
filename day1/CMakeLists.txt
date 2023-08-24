project(iio_apps)

#add_executable(hello hello.c)
#add_executable(hello_iio hello_iio.c)
#add_executable(ctx_attr ctx_attr.c)
#add_executable(part1 part1.c)
#add_executable(part2 part2.c)
#add_executable(part3 part3.c)
#add_executable(part4 part4.c)
#add_executable(read_chans read_chans.c) #numele executabilului si fisierul meu
#add_executable(shock_detect shock_detect.c)
add_executable(buffer buffer.c)


#target_link_libraries(hello_iio iio)
#target_link_libraries(ctx_attr iio)
#target_link_libraries(part1 iio)
#target_link_libraries(part2 iio)
#arget_link_libraries(part3 iio)
#target_link_libraries(part4 iio)
#target_link_libraries(read_chans iio)
#target_link_libraries(shock_detect iio)
target_link_libraries(buffer iio)