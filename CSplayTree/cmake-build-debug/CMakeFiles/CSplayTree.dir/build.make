# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/dave/Downloads/clion-2018.2.6/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/dave/Downloads/clion-2018.2.6/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dave/CSplayTree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dave/CSplayTree/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CSplayTree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CSplayTree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CSplayTree.dir/flags.make

CMakeFiles/CSplayTree.dir/SplayTree.c.o: CMakeFiles/CSplayTree.dir/flags.make
CMakeFiles/CSplayTree.dir/SplayTree.c.o: ../SplayTree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dave/CSplayTree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CSplayTree.dir/SplayTree.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CSplayTree.dir/SplayTree.c.o   -c /home/dave/CSplayTree/SplayTree.c

CMakeFiles/CSplayTree.dir/SplayTree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CSplayTree.dir/SplayTree.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dave/CSplayTree/SplayTree.c > CMakeFiles/CSplayTree.dir/SplayTree.c.i

CMakeFiles/CSplayTree.dir/SplayTree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CSplayTree.dir/SplayTree.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dave/CSplayTree/SplayTree.c -o CMakeFiles/CSplayTree.dir/SplayTree.c.s

CMakeFiles/CSplayTree.dir/SplayTreeTests.c.o: CMakeFiles/CSplayTree.dir/flags.make
CMakeFiles/CSplayTree.dir/SplayTreeTests.c.o: ../SplayTreeTests.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dave/CSplayTree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/CSplayTree.dir/SplayTreeTests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CSplayTree.dir/SplayTreeTests.c.o   -c /home/dave/CSplayTree/SplayTreeTests.c

CMakeFiles/CSplayTree.dir/SplayTreeTests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CSplayTree.dir/SplayTreeTests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dave/CSplayTree/SplayTreeTests.c > CMakeFiles/CSplayTree.dir/SplayTreeTests.c.i

CMakeFiles/CSplayTree.dir/SplayTreeTests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CSplayTree.dir/SplayTreeTests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dave/CSplayTree/SplayTreeTests.c -o CMakeFiles/CSplayTree.dir/SplayTreeTests.c.s

# Object files for target CSplayTree
CSplayTree_OBJECTS = \
"CMakeFiles/CSplayTree.dir/SplayTree.c.o" \
"CMakeFiles/CSplayTree.dir/SplayTreeTests.c.o"

# External object files for target CSplayTree
CSplayTree_EXTERNAL_OBJECTS =

CSplayTree: CMakeFiles/CSplayTree.dir/SplayTree.c.o
CSplayTree: CMakeFiles/CSplayTree.dir/SplayTreeTests.c.o
CSplayTree: CMakeFiles/CSplayTree.dir/build.make
CSplayTree: CMakeFiles/CSplayTree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dave/CSplayTree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable CSplayTree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CSplayTree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CSplayTree.dir/build: CSplayTree

.PHONY : CMakeFiles/CSplayTree.dir/build

CMakeFiles/CSplayTree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CSplayTree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CSplayTree.dir/clean

CMakeFiles/CSplayTree.dir/depend:
	cd /home/dave/CSplayTree/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dave/CSplayTree /home/dave/CSplayTree /home/dave/CSplayTree/cmake-build-debug /home/dave/CSplayTree/cmake-build-debug /home/dave/CSplayTree/cmake-build-debug/CMakeFiles/CSplayTree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CSplayTree.dir/depend

