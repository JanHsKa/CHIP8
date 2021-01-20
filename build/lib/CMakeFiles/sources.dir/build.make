# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/janmalle/Studium/Semester5/Projektarbeit/Chip8

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/sources.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/sources.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/sources.dir/flags.make

lib/CMakeFiles/sources.dir/Chip8.cpp.o: lib/CMakeFiles/sources.dir/flags.make
lib/CMakeFiles/sources.dir/Chip8.cpp.o: ../lib/Chip8.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/sources.dir/Chip8.cpp.o"
	cd /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build/lib && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sources.dir/Chip8.cpp.o -c /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/lib/Chip8.cpp

lib/CMakeFiles/sources.dir/Chip8.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sources.dir/Chip8.cpp.i"
	cd /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build/lib && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/lib/Chip8.cpp > CMakeFiles/sources.dir/Chip8.cpp.i

lib/CMakeFiles/sources.dir/Chip8.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sources.dir/Chip8.cpp.s"
	cd /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build/lib && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/lib/Chip8.cpp -o CMakeFiles/sources.dir/Chip8.cpp.s

lib/CMakeFiles/sources.dir/Controller.cpp.o: lib/CMakeFiles/sources.dir/flags.make
lib/CMakeFiles/sources.dir/Controller.cpp.o: ../lib/Controller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/sources.dir/Controller.cpp.o"
	cd /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build/lib && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sources.dir/Controller.cpp.o -c /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/lib/Controller.cpp

lib/CMakeFiles/sources.dir/Controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sources.dir/Controller.cpp.i"
	cd /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build/lib && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/lib/Controller.cpp > CMakeFiles/sources.dir/Controller.cpp.i

lib/CMakeFiles/sources.dir/Controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sources.dir/Controller.cpp.s"
	cd /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build/lib && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/lib/Controller.cpp -o CMakeFiles/sources.dir/Controller.cpp.s

# Object files for target sources
sources_OBJECTS = \
"CMakeFiles/sources.dir/Chip8.cpp.o" \
"CMakeFiles/sources.dir/Controller.cpp.o"

# External object files for target sources
sources_EXTERNAL_OBJECTS =

lib/libsources.so: lib/CMakeFiles/sources.dir/Chip8.cpp.o
lib/libsources.so: lib/CMakeFiles/sources.dir/Controller.cpp.o
lib/libsources.so: lib/CMakeFiles/sources.dir/build.make
lib/libsources.so: lib/CMakeFiles/sources.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libsources.so"
	cd /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sources.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/sources.dir/build: lib/libsources.so

.PHONY : lib/CMakeFiles/sources.dir/build

lib/CMakeFiles/sources.dir/clean:
	cd /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/sources.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/sources.dir/clean

lib/CMakeFiles/sources.dir/depend:
	cd /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/janmalle/Studium/Semester5/Projektarbeit/Chip8 /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/lib /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build/lib /home/janmalle/Studium/Semester5/Projektarbeit/Chip8/build/lib/CMakeFiles/sources.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/sources.dir/depend

