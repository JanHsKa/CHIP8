cmake_minimum_required(VERSION 3.0.0)
project(Chip8 VERSION 1.0.0)

include(CTest)
enable_testing()


#include_directories(include)

add_subdirectory(lib)
add_subdirectory(main)


#add_subdirectory(src)




set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
