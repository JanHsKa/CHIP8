
include_directories(${CMAKE_SOURCE_DIR}/lib)
#include_directories(${CMAKE_SOURCE_DIR}/lib/header)


add_executable(CHIP8 main.cpp)

target_link_libraries(CHIP8 sources)

#target_link_libraries(CHIP8 header)


find_package(SDL2 REQUIRED)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

include_directories(CHIP8 ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

target_link_libraries(CHIP8 ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES}) 

install(TARGETS CHIP8 DESTINATION bin)

