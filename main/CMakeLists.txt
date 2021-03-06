
include_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(CHIP8 main.cpp)

target_link_libraries(CHIP8 sources)

find_package(SDL2 REQUIRED)
include_directories(CHIP8 ${SDL2_INCLUDE_DIRS})

target_link_libraries(CHIP8 ${SDL2_LIBRARIES}) 

install(TARGETS CHIP8 DESTINATION bin)

