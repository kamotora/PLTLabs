# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /home/artem/clion-2019.2.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/artem/clion-2019.2.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/artem/compC++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/artem/compC++/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/compC__.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/compC__.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compC__.dir/flags.make

CMakeFiles/compC__.dir/main.cpp.o: CMakeFiles/compC__.dir/flags.make
CMakeFiles/compC__.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artem/compC++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/compC__.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compC__.dir/main.cpp.o -c /home/artem/compC++/main.cpp

CMakeFiles/compC__.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compC__.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artem/compC++/main.cpp > CMakeFiles/compC__.dir/main.cpp.i

CMakeFiles/compC__.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compC__.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artem/compC++/main.cpp -o CMakeFiles/compC__.dir/main.cpp.s

CMakeFiles/compC__.dir/Scanner.cpp.o: CMakeFiles/compC__.dir/flags.make
CMakeFiles/compC__.dir/Scanner.cpp.o: ../Scanner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artem/compC++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/compC__.dir/Scanner.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compC__.dir/Scanner.cpp.o -c /home/artem/compC++/Scanner.cpp

CMakeFiles/compC__.dir/Scanner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compC__.dir/Scanner.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artem/compC++/Scanner.cpp > CMakeFiles/compC__.dir/Scanner.cpp.i

CMakeFiles/compC__.dir/Scanner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compC__.dir/Scanner.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artem/compC++/Scanner.cpp -o CMakeFiles/compC__.dir/Scanner.cpp.s

CMakeFiles/compC__.dir/Diagram.cpp.o: CMakeFiles/compC__.dir/flags.make
CMakeFiles/compC__.dir/Diagram.cpp.o: ../Diagram.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artem/compC++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/compC__.dir/Diagram.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compC__.dir/Diagram.cpp.o -c /home/artem/compC++/Diagram.cpp

CMakeFiles/compC__.dir/Diagram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compC__.dir/Diagram.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artem/compC++/Diagram.cpp > CMakeFiles/compC__.dir/Diagram.cpp.i

CMakeFiles/compC__.dir/Diagram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compC__.dir/Diagram.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artem/compC++/Diagram.cpp -o CMakeFiles/compC__.dir/Diagram.cpp.s

# Object files for target compC__
compC___OBJECTS = \
"CMakeFiles/compC__.dir/main.cpp.o" \
"CMakeFiles/compC__.dir/Scanner.cpp.o" \
"CMakeFiles/compC__.dir/Diagram.cpp.o"

# External object files for target compC__
compC___EXTERNAL_OBJECTS =

compC__: CMakeFiles/compC__.dir/main.cpp.o
compC__: CMakeFiles/compC__.dir/Scanner.cpp.o
compC__: CMakeFiles/compC__.dir/Diagram.cpp.o
compC__: CMakeFiles/compC__.dir/build.make
compC__: CMakeFiles/compC__.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/artem/compC++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable compC__"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compC__.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compC__.dir/build: compC__

.PHONY : CMakeFiles/compC__.dir/build

CMakeFiles/compC__.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compC__.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compC__.dir/clean

CMakeFiles/compC__.dir/depend:
	cd /home/artem/compC++/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/artem/compC++ /home/artem/compC++ /home/artem/compC++/cmake-build-debug /home/artem/compC++/cmake-build-debug /home/artem/compC++/cmake-build-debug/CMakeFiles/compC__.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compC__.dir/depend

