# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/elkmir/work/open62541/examples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/elkmir/work/open62541/examples

# Include any dependencies generated for this target.
include CMakeFiles/client_connectivitycheck_loop.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/client_connectivitycheck_loop.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client_connectivitycheck_loop.dir/flags.make

CMakeFiles/client_connectivitycheck_loop.dir/client_connectivitycheck_loop.c.o: CMakeFiles/client_connectivitycheck_loop.dir/flags.make
CMakeFiles/client_connectivitycheck_loop.dir/client_connectivitycheck_loop.c.o: client_connectivitycheck_loop.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/elkmir/work/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/client_connectivitycheck_loop.dir/client_connectivitycheck_loop.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/client_connectivitycheck_loop.dir/client_connectivitycheck_loop.c.o   -c /home/elkmir/work/open62541/examples/client_connectivitycheck_loop.c

CMakeFiles/client_connectivitycheck_loop.dir/client_connectivitycheck_loop.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client_connectivitycheck_loop.dir/client_connectivitycheck_loop.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/elkmir/work/open62541/examples/client_connectivitycheck_loop.c > CMakeFiles/client_connectivitycheck_loop.dir/client_connectivitycheck_loop.c.i

CMakeFiles/client_connectivitycheck_loop.dir/client_connectivitycheck_loop.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client_connectivitycheck_loop.dir/client_connectivitycheck_loop.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/elkmir/work/open62541/examples/client_connectivitycheck_loop.c -o CMakeFiles/client_connectivitycheck_loop.dir/client_connectivitycheck_loop.c.s

# Object files for target client_connectivitycheck_loop
client_connectivitycheck_loop_OBJECTS = \
"CMakeFiles/client_connectivitycheck_loop.dir/client_connectivitycheck_loop.c.o"

# External object files for target client_connectivitycheck_loop
client_connectivitycheck_loop_EXTERNAL_OBJECTS =

bin/examples/client_connectivitycheck_loop: CMakeFiles/client_connectivitycheck_loop.dir/client_connectivitycheck_loop.c.o
bin/examples/client_connectivitycheck_loop: CMakeFiles/client_connectivitycheck_loop.dir/build.make
bin/examples/client_connectivitycheck_loop: /usr/local/lib/libopen62541.a
bin/examples/client_connectivitycheck_loop: CMakeFiles/client_connectivitycheck_loop.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/elkmir/work/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/examples/client_connectivitycheck_loop"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client_connectivitycheck_loop.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client_connectivitycheck_loop.dir/build: bin/examples/client_connectivitycheck_loop

.PHONY : CMakeFiles/client_connectivitycheck_loop.dir/build

CMakeFiles/client_connectivitycheck_loop.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client_connectivitycheck_loop.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client_connectivitycheck_loop.dir/clean

CMakeFiles/client_connectivitycheck_loop.dir/depend:
	cd /home/elkmir/work/open62541/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples/CMakeFiles/client_connectivitycheck_loop.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client_connectivitycheck_loop.dir/depend

