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
include CMakeFiles/server_repeated_job.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server_repeated_job.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server_repeated_job.dir/flags.make

CMakeFiles/server_repeated_job.dir/server_repeated_job.c.o: CMakeFiles/server_repeated_job.dir/flags.make
CMakeFiles/server_repeated_job.dir/server_repeated_job.c.o: server_repeated_job.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/elkmir/work/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/server_repeated_job.dir/server_repeated_job.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server_repeated_job.dir/server_repeated_job.c.o   -c /home/elkmir/work/open62541/examples/server_repeated_job.c

CMakeFiles/server_repeated_job.dir/server_repeated_job.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server_repeated_job.dir/server_repeated_job.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/elkmir/work/open62541/examples/server_repeated_job.c > CMakeFiles/server_repeated_job.dir/server_repeated_job.c.i

CMakeFiles/server_repeated_job.dir/server_repeated_job.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server_repeated_job.dir/server_repeated_job.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/elkmir/work/open62541/examples/server_repeated_job.c -o CMakeFiles/server_repeated_job.dir/server_repeated_job.c.s

# Object files for target server_repeated_job
server_repeated_job_OBJECTS = \
"CMakeFiles/server_repeated_job.dir/server_repeated_job.c.o"

# External object files for target server_repeated_job
server_repeated_job_EXTERNAL_OBJECTS =

bin/examples/server_repeated_job: CMakeFiles/server_repeated_job.dir/server_repeated_job.c.o
bin/examples/server_repeated_job: CMakeFiles/server_repeated_job.dir/build.make
bin/examples/server_repeated_job: /usr/local/lib/libopen62541.a
bin/examples/server_repeated_job: CMakeFiles/server_repeated_job.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/elkmir/work/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/examples/server_repeated_job"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server_repeated_job.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server_repeated_job.dir/build: bin/examples/server_repeated_job

.PHONY : CMakeFiles/server_repeated_job.dir/build

CMakeFiles/server_repeated_job.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server_repeated_job.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server_repeated_job.dir/clean

CMakeFiles/server_repeated_job.dir/depend:
	cd /home/elkmir/work/open62541/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples/CMakeFiles/server_repeated_job.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server_repeated_job.dir/depend

