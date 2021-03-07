
set (libSrcs Chip8.cpp Emulator.cpp Display.cpp)

add_library(sources SHARED ${libSrcs})

install(TARGETS sources DESTINATION lib)
