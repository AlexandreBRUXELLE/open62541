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
include CMakeFiles/tutorial_client_firststeps.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tutorial_client_firststeps.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tutorial_client_firststeps.dir/flags.make

CMakeFiles/tutorial_client_firststeps.dir/tutorial_client_firststeps.c.o: CMakeFiles/tutorial_client_firststeps.dir/flags.make
CMakeFiles/tutorial_client_firststeps.dir/tutorial_client_firststeps.c.o: tutorial_client_firststeps.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/elkmir/work/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tutorial_client_firststeps.dir/tutorial_client_firststeps.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tutorial_client_firststeps.dir/tutorial_client_firststeps.c.o   -c /home/elkmir/work/open62541/examples/tutorial_client_firststeps.c

CMakeFiles/tutorial_client_firststeps.dir/tutorial_client_firststeps.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tutorial_client_firststeps.dir/tutorial_client_firststeps.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/elkmir/work/open62541/examples/tutorial_client_firststeps.c > CMakeFiles/tutorial_client_firststeps.dir/tutorial_client_firststeps.c.i

CMakeFiles/tutorial_client_firststeps.dir/tutorial_client_firststeps.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tutorial_client_firststeps.dir/tutorial_client_firststeps.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/elkmir/work/open62541/examples/tutorial_client_firststeps.c -o CMakeFiles/tutorial_client_firststeps.dir/tutorial_client_firststeps.c.s

# Object files for target tutorial_client_firststeps
tutorial_client_firststeps_OBJECTS = \
"CMakeFiles/tutorial_client_firststeps.dir/tutorial_client_firststeps.c.o"

# External object files for target tutorial_client_firststeps
tutorial_client_firststeps_EXTERNAL_OBJECTS =

bin/examples/tutorial_client_firststeps: CMakeFiles/tutorial_client_firststeps.dir/tutorial_client_firststeps.c.o
bin/examples/tutorial_client_firststeps: CMakeFiles/tutorial_client_firststeps.dir/build.make
bin/examples/tutorial_client_firststeps: /usr/local/lib/libopen62541.a
bin/examples/tutorial_client_firststeps: CMakeFiles/tutorial_client_firststeps.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/elkmir/work/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/examples/tutorial_client_firststeps"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tutorial_client_firststeps.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tutorial_client_firststeps.dir/build: bin/examples/tutorial_client_firststeps

.PHONY : CMakeFiles/tutorial_client_firststeps.dir/build

CMakeFiles/tutorial_client_firststeps.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tutorial_client_firststeps.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tutorial_client_firststeps.dir/clean

CMakeFiles/tutorial_client_firststeps.dir/depend:
	cd /home/elkmir/work/open62541/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples/CMakeFiles/tutorial_client_firststeps.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tutorial_client_firststeps.dir/depend

