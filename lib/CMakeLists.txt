
set (libSrcs Chip8.cpp Controller.cpp)

add_library(sources SHARED ${libSrcs})

install(TARGETS sources DESTINATION lib)
