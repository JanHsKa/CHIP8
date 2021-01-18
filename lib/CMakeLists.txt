
set (libSrcs chip8.cpp controller.cpp)

add_library(sources SHARED ${libSrcs})

install(TARGETS sources DESTINATION lib)
