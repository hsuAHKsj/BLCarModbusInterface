# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/orangepi/Desktop/BLCarModbusInterface

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/orangepi/Desktop/BLCarModbusInterface/build

# Include any dependencies generated for this target.
include CMakeFiles/testTCPClient.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/testTCPClient.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/testTCPClient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testTCPClient.dir/flags.make

CMakeFiles/testTCPClient.dir/test/cpp/TCPClient.cpp.o: CMakeFiles/testTCPClient.dir/flags.make
CMakeFiles/testTCPClient.dir/test/cpp/TCPClient.cpp.o: ../test/cpp/TCPClient.cpp
CMakeFiles/testTCPClient.dir/test/cpp/TCPClient.cpp.o: CMakeFiles/testTCPClient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orangepi/Desktop/BLCarModbusInterface/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testTCPClient.dir/test/cpp/TCPClient.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testTCPClient.dir/test/cpp/TCPClient.cpp.o -MF CMakeFiles/testTCPClient.dir/test/cpp/TCPClient.cpp.o.d -o CMakeFiles/testTCPClient.dir/test/cpp/TCPClient.cpp.o -c /home/orangepi/Desktop/BLCarModbusInterface/test/cpp/TCPClient.cpp

CMakeFiles/testTCPClient.dir/test/cpp/TCPClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testTCPClient.dir/test/cpp/TCPClient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orangepi/Desktop/BLCarModbusInterface/test/cpp/TCPClient.cpp > CMakeFiles/testTCPClient.dir/test/cpp/TCPClient.cpp.i

CMakeFiles/testTCPClient.dir/test/cpp/TCPClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testTCPClient.dir/test/cpp/TCPClient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orangepi/Desktop/BLCarModbusInterface/test/cpp/TCPClient.cpp -o CMakeFiles/testTCPClient.dir/test/cpp/TCPClient.cpp.s

# Object files for target testTCPClient
testTCPClient_OBJECTS = \
"CMakeFiles/testTCPClient.dir/test/cpp/TCPClient.cpp.o"

# External object files for target testTCPClient
testTCPClient_EXTERNAL_OBJECTS =

testTCPClient: CMakeFiles/testTCPClient.dir/test/cpp/TCPClient.cpp.o
testTCPClient: CMakeFiles/testTCPClient.dir/build.make
testTCPClient: CMakeFiles/testTCPClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orangepi/Desktop/BLCarModbusInterface/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testTCPClient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testTCPClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testTCPClient.dir/build: testTCPClient
.PHONY : CMakeFiles/testTCPClient.dir/build

CMakeFiles/testTCPClient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testTCPClient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testTCPClient.dir/clean

CMakeFiles/testTCPClient.dir/depend:
	cd /home/orangepi/Desktop/BLCarModbusInterface/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orangepi/Desktop/BLCarModbusInterface /home/orangepi/Desktop/BLCarModbusInterface /home/orangepi/Desktop/BLCarModbusInterface/build /home/orangepi/Desktop/BLCarModbusInterface/build /home/orangepi/Desktop/BLCarModbusInterface/build/CMakeFiles/testTCPClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testTCPClient.dir/depend
