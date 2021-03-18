
set (libSrcs CPU.cpp Emulator.cpp GameDisplay.cpp Keypad.cpp Soundcontroller.cpp DebugTexture.cpp DebugDisplay.cpp InputChecker.cpp DebugManager.cpp) 


add_library(sources SHARED ${libSrcs})

install(TARGETS sources DESTINATION lib)


#add_library(header INTERFACE)

#target_sources(header INTERFACE Display.h)

#target_include_directories(header INTERFACE ../header/Display.h)