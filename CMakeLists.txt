cmake_minimum_required(VERSION 3.0.0)
project(Chip8 CXX)

include(CTest)
enable_testing()

set(CMAKE_BUILD_TYPE Debug)


#set(CMAKE_L_FLAGS "sdl2-config --libs` -lSDL2_ttf")
#include_directories(include)
add_subdirectory(lib)
add_subdirectory(main)
#add_subdirectory(lib/header)



#add_subdirectory(src)




set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
