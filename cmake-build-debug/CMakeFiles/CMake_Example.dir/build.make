# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/long/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.5981.166/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/long/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.5981.166/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/long/Desktop/serial-port-plotting

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/long/Desktop/serial-port-plotting/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CMake_Example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CMake_Example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CMake_Example.dir/flags.make

CMakeFiles/CMake_Example.dir/src/Common.cpp.o: CMakeFiles/CMake_Example.dir/flags.make
CMakeFiles/CMake_Example.dir/src/Common.cpp.o: ../src/Common.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/long/Desktop/serial-port-plotting/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CMake_Example.dir/src/Common.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CMake_Example.dir/src/Common.cpp.o -c /home/long/Desktop/serial-port-plotting/src/Common.cpp

CMakeFiles/CMake_Example.dir/src/Common.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CMake_Example.dir/src/Common.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/long/Desktop/serial-port-plotting/src/Common.cpp > CMakeFiles/CMake_Example.dir/src/Common.cpp.i

CMakeFiles/CMake_Example.dir/src/Common.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CMake_Example.dir/src/Common.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/long/Desktop/serial-port-plotting/src/Common.cpp -o CMakeFiles/CMake_Example.dir/src/Common.cpp.s

CMakeFiles/CMake_Example.dir/src/Exception.cpp.o: CMakeFiles/CMake_Example.dir/flags.make
CMakeFiles/CMake_Example.dir/src/Exception.cpp.o: ../src/Exception.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/long/Desktop/serial-port-plotting/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CMake_Example.dir/src/Exception.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CMake_Example.dir/src/Exception.cpp.o -c /home/long/Desktop/serial-port-plotting/src/Exception.cpp

CMakeFiles/CMake_Example.dir/src/Exception.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CMake_Example.dir/src/Exception.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/long/Desktop/serial-port-plotting/src/Exception.cpp > CMakeFiles/CMake_Example.dir/src/Exception.cpp.i

CMakeFiles/CMake_Example.dir/src/Exception.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CMake_Example.dir/src/Exception.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/long/Desktop/serial-port-plotting/src/Exception.cpp -o CMakeFiles/CMake_Example.dir/src/Exception.cpp.s

# Object files for target CMake_Example
CMake_Example_OBJECTS = \
"CMakeFiles/CMake_Example.dir/src/Common.cpp.o" \
"CMakeFiles/CMake_Example.dir/src/Exception.cpp.o"

# External object files for target CMake_Example
CMake_Example_EXTERNAL_OBJECTS =

libCMake_Example.so: CMakeFiles/CMake_Example.dir/src/Common.cpp.o
libCMake_Example.so: CMakeFiles/CMake_Example.dir/src/Exception.cpp.o
libCMake_Example.so: CMakeFiles/CMake_Example.dir/build.make
libCMake_Example.so: CMakeFiles/CMake_Example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/long/Desktop/serial-port-plotting/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libCMake_Example.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CMake_Example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CMake_Example.dir/build: libCMake_Example.so

.PHONY : CMakeFiles/CMake_Example.dir/build

CMakeFiles/CMake_Example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CMake_Example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CMake_Example.dir/clean

CMakeFiles/CMake_Example.dir/depend:
	cd /home/long/Desktop/serial-port-plotting/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/long/Desktop/serial-port-plotting /home/long/Desktop/serial-port-plotting /home/long/Desktop/serial-port-plotting/cmake-build-debug /home/long/Desktop/serial-port-plotting/cmake-build-debug /home/long/Desktop/serial-port-plotting/cmake-build-debug/CMakeFiles/CMake_Example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CMake_Example.dir/depend

