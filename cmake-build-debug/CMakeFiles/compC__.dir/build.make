# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /home/kamotora/jetbrains/apps/CLion/ch-0/211.4961.39/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/kamotora/jetbrains/apps/CLion/ch-0/211.4961.39/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kamotora/compC++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kamotora/compC++/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/compC__.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/compC__.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compC__.dir/flags.make

CMakeFiles/compC__.dir/main.cpp.o: CMakeFiles/compC__.dir/flags.make
CMakeFiles/compC__.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kamotora/compC++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/compC__.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compC__.dir/main.cpp.o -c /home/kamotora/compC++/main.cpp

CMakeFiles/compC__.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compC__.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kamotora/compC++/main.cpp > CMakeFiles/compC__.dir/main.cpp.i

CMakeFiles/compC__.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compC__.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kamotora/compC++/main.cpp -o CMakeFiles/compC__.dir/main.cpp.s

CMakeFiles/compC__.dir/Scanner.cpp.o: CMakeFiles/compC__.dir/flags.make
CMakeFiles/compC__.dir/Scanner.cpp.o: ../Scanner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kamotora/compC++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/compC__.dir/Scanner.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compC__.dir/Scanner.cpp.o -c /home/kamotora/compC++/Scanner.cpp

CMakeFiles/compC__.dir/Scanner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compC__.dir/Scanner.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kamotora/compC++/Scanner.cpp > CMakeFiles/compC__.dir/Scanner.cpp.i

CMakeFiles/compC__.dir/Scanner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compC__.dir/Scanner.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kamotora/compC++/Scanner.cpp -o CMakeFiles/compC__.dir/Scanner.cpp.s

CMakeFiles/compC__.dir/Diagram.cpp.o: CMakeFiles/compC__.dir/flags.make
CMakeFiles/compC__.dir/Diagram.cpp.o: ../Diagram.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kamotora/compC++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/compC__.dir/Diagram.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compC__.dir/Diagram.cpp.o -c /home/kamotora/compC++/Diagram.cpp

CMakeFiles/compC__.dir/Diagram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compC__.dir/Diagram.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kamotora/compC++/Diagram.cpp > CMakeFiles/compC__.dir/Diagram.cpp.i

CMakeFiles/compC__.dir/Diagram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compC__.dir/Diagram.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kamotora/compC++/Diagram.cpp -o CMakeFiles/compC__.dir/Diagram.cpp.s

CMakeFiles/compC__.dir/Tree.cpp.o: CMakeFiles/compC__.dir/flags.make
CMakeFiles/compC__.dir/Tree.cpp.o: ../Tree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kamotora/compC++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/compC__.dir/Tree.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compC__.dir/Tree.cpp.o -c /home/kamotora/compC++/Tree.cpp

CMakeFiles/compC__.dir/Tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compC__.dir/Tree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kamotora/compC++/Tree.cpp > CMakeFiles/compC__.dir/Tree.cpp.i

CMakeFiles/compC__.dir/Tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compC__.dir/Tree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kamotora/compC++/Tree.cpp -o CMakeFiles/compC__.dir/Tree.cpp.s

CMakeFiles/compC__.dir/defs.cpp.o: CMakeFiles/compC__.dir/flags.make
CMakeFiles/compC__.dir/defs.cpp.o: ../defs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kamotora/compC++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/compC__.dir/defs.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compC__.dir/defs.cpp.o -c /home/kamotora/compC++/defs.cpp

CMakeFiles/compC__.dir/defs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compC__.dir/defs.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kamotora/compC++/defs.cpp > CMakeFiles/compC__.dir/defs.cpp.i

CMakeFiles/compC__.dir/defs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compC__.dir/defs.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kamotora/compC++/defs.cpp -o CMakeFiles/compC__.dir/defs.cpp.s

CMakeFiles/compC__.dir/LL1.cpp.o: CMakeFiles/compC__.dir/flags.make
CMakeFiles/compC__.dir/LL1.cpp.o: ../LL1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kamotora/compC++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/compC__.dir/LL1.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compC__.dir/LL1.cpp.o -c /home/kamotora/compC++/LL1.cpp

CMakeFiles/compC__.dir/LL1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compC__.dir/LL1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kamotora/compC++/LL1.cpp > CMakeFiles/compC__.dir/LL1.cpp.i

CMakeFiles/compC__.dir/LL1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compC__.dir/LL1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kamotora/compC++/LL1.cpp -o CMakeFiles/compC__.dir/LL1.cpp.s

CMakeFiles/compC__.dir/Semant.cpp.o: CMakeFiles/compC__.dir/flags.make
CMakeFiles/compC__.dir/Semant.cpp.o: ../Semant.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kamotora/compC++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/compC__.dir/Semant.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compC__.dir/Semant.cpp.o -c /home/kamotora/compC++/Semant.cpp

CMakeFiles/compC__.dir/Semant.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compC__.dir/Semant.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kamotora/compC++/Semant.cpp > CMakeFiles/compC__.dir/Semant.cpp.i

CMakeFiles/compC__.dir/Semant.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compC__.dir/Semant.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kamotora/compC++/Semant.cpp -o CMakeFiles/compC__.dir/Semant.cpp.s

# Object files for target compC__
compC___OBJECTS = \
"CMakeFiles/compC__.dir/main.cpp.o" \
"CMakeFiles/compC__.dir/Scanner.cpp.o" \
"CMakeFiles/compC__.dir/Diagram.cpp.o" \
"CMakeFiles/compC__.dir/Tree.cpp.o" \
"CMakeFiles/compC__.dir/defs.cpp.o" \
"CMakeFiles/compC__.dir/LL1.cpp.o" \
"CMakeFiles/compC__.dir/Semant.cpp.o"

# External object files for target compC__
compC___EXTERNAL_OBJECTS =

compC__: CMakeFiles/compC__.dir/main.cpp.o
compC__: CMakeFiles/compC__.dir/Scanner.cpp.o
compC__: CMakeFiles/compC__.dir/Diagram.cpp.o
compC__: CMakeFiles/compC__.dir/Tree.cpp.o
compC__: CMakeFiles/compC__.dir/defs.cpp.o
compC__: CMakeFiles/compC__.dir/LL1.cpp.o
compC__: CMakeFiles/compC__.dir/Semant.cpp.o
compC__: CMakeFiles/compC__.dir/build.make
compC__: CMakeFiles/compC__.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kamotora/compC++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable compC__"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compC__.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compC__.dir/build: compC__

.PHONY : CMakeFiles/compC__.dir/build

CMakeFiles/compC__.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compC__.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compC__.dir/clean

CMakeFiles/compC__.dir/depend:
	cd /home/kamotora/compC++/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kamotora/compC++ /home/kamotora/compC++ /home/kamotora/compC++/cmake-build-debug /home/kamotora/compC++/cmake-build-debug /home/kamotora/compC++/cmake-build-debug/CMakeFiles/compC__.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compC__.dir/depend

