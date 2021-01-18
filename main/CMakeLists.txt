
include_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(mainProgram main.cpp)

target_link_libraries(mainProgram sources)

find_package(SDL2 REQUIRED)
include_directories(CHIP8 ${SDL2_INCLUDE_DIRS})

target_link_libraries(mainProgram ${SDL2_LIBRARIES}) 

install(TARGETS mainProgram DESTINATION bin)

