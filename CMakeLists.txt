cmake_minimum_required(VERSION 3.5)
project(isletim_sistemleri_ikinci_odev)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        write.c)

add_test(isletim_sistemleri_ikinci_odev read.c)
add_executable(isletim_sistemleri_ikinci_odev ${SOURCE_FILES})