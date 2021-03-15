
set (libSrcs Chip8.cpp Emulator.cpp Display.cpp Keypad.cpp Soundcontroller.cpp DebugTexture.cpp)

add_library(sources SHARED ${libSrcs})

install(TARGETS sources DESTINATION lib)
