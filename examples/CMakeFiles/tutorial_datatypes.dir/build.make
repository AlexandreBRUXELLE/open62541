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
include CMakeFiles/tutorial_datatypes.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tutorial_datatypes.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tutorial_datatypes.dir/flags.make

CMakeFiles/tutorial_datatypes.dir/tutorial_datatypes.c.o: CMakeFiles/tutorial_datatypes.dir/flags.make
CMakeFiles/tutorial_datatypes.dir/tutorial_datatypes.c.o: tutorial_datatypes.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/elkmir/work/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tutorial_datatypes.dir/tutorial_datatypes.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tutorial_datatypes.dir/tutorial_datatypes.c.o   -c /home/elkmir/work/open62541/examples/tutorial_datatypes.c

CMakeFiles/tutorial_datatypes.dir/tutorial_datatypes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tutorial_datatypes.dir/tutorial_datatypes.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/elkmir/work/open62541/examples/tutorial_datatypes.c > CMakeFiles/tutorial_datatypes.dir/tutorial_datatypes.c.i

CMakeFiles/tutorial_datatypes.dir/tutorial_datatypes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tutorial_datatypes.dir/tutorial_datatypes.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/elkmir/work/open62541/examples/tutorial_datatypes.c -o CMakeFiles/tutorial_datatypes.dir/tutorial_datatypes.c.s

# Object files for target tutorial_datatypes
tutorial_datatypes_OBJECTS = \
"CMakeFiles/tutorial_datatypes.dir/tutorial_datatypes.c.o"

# External object files for target tutorial_datatypes
tutorial_datatypes_EXTERNAL_OBJECTS =

bin/examples/tutorial_datatypes: CMakeFiles/tutorial_datatypes.dir/tutorial_datatypes.c.o
bin/examples/tutorial_datatypes: CMakeFiles/tutorial_datatypes.dir/build.make
bin/examples/tutorial_datatypes: /usr/local/lib/libopen62541.a
bin/examples/tutorial_datatypes: CMakeFiles/tutorial_datatypes.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/elkmir/work/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/examples/tutorial_datatypes"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tutorial_datatypes.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tutorial_datatypes.dir/build: bin/examples/tutorial_datatypes

.PHONY : CMakeFiles/tutorial_datatypes.dir/build

CMakeFiles/tutorial_datatypes.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tutorial_datatypes.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tutorial_datatypes.dir/clean

CMakeFiles/tutorial_datatypes.dir/depend:
	cd /home/elkmir/work/open62541/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples/CMakeFiles/tutorial_datatypes.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tutorial_datatypes.dir/depend

