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

# Utility rule file for open62541-generator-ns-example.

# Include the progress variables for this target.
include nodeset/CMakeFiles/open62541-generator-ns-example.dir/progress.make

nodeset/CMakeFiles/open62541-generator-ns-example: src_generated/open62541/namespace_example_generated.c
nodeset/CMakeFiles/open62541-generator-ns-example: src_generated/open62541/namespace_example_generated.h


src_generated/open62541/namespace_example_generated.c: /usr/local/share/open62541/tools/nodeset_compiler/nodeset_compiler.py
src_generated/open62541/namespace_example_generated.c: /usr/local/share/open62541/tools/nodeset_compiler/nodes.py
src_generated/open62541/namespace_example_generated.c: /usr/local/share/open62541/tools/nodeset_compiler/nodeset.py
src_generated/open62541/namespace_example_generated.c: /usr/local/share/open62541/tools/nodeset_compiler/datatypes.py
src_generated/open62541/namespace_example_generated.c: /usr/local/share/open62541/tools/nodeset_compiler/backend_open62541.py
src_generated/open62541/namespace_example_generated.c: /usr/local/share/open62541/tools/nodeset_compiler/backend_open62541_nodes.py
src_generated/open62541/namespace_example_generated.c: /usr/local/share/open62541/tools/nodeset_compiler/backend_open62541_datatypes.py
src_generated/open62541/namespace_example_generated.c: nodeset/server_nodeset.xml
src_generated/open62541/namespace_example_generated.c: /usr/local/share/open62541/tools/ua-nodeset/Schema/Opc.Ua.NodeSet2.xml
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/elkmir/work/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating ../src_generated/open62541/namespace_example_generated.c, ../src_generated/open62541/namespace_example_generated.h"
	cd /home/elkmir/work/open62541/examples/nodeset && /usr/bin/python3.8 /usr/local/share/open62541/tools/nodeset_compiler/nodeset_compiler.py --types-array=UA_TYPES --types-array=UA_TYPES --existing=/usr/local/share/open62541/tools/ua-nodeset/Schema/Opc.Ua.NodeSet2.xml --xml=/home/elkmir/work/open62541/examples/nodeset/server_nodeset.xml /home/elkmir/work/open62541/examples/src_generated/open62541/namespace_example_generated

src_generated/open62541/namespace_example_generated.h: src_generated/open62541/namespace_example_generated.c
	@$(CMAKE_COMMAND) -E touch_nocreate src_generated/open62541/namespace_example_generated.h

open62541-generator-ns-example: nodeset/CMakeFiles/open62541-generator-ns-example
open62541-generator-ns-example: src_generated/open62541/namespace_example_generated.c
open62541-generator-ns-example: src_generated/open62541/namespace_example_generated.h
open62541-generator-ns-example: nodeset/CMakeFiles/open62541-generator-ns-example.dir/build.make

.PHONY : open62541-generator-ns-example

# Rule to build all files generated by this target.
nodeset/CMakeFiles/open62541-generator-ns-example.dir/build: open62541-generator-ns-example

.PHONY : nodeset/CMakeFiles/open62541-generator-ns-example.dir/build

nodeset/CMakeFiles/open62541-generator-ns-example.dir/clean:
	cd /home/elkmir/work/open62541/examples/nodeset && $(CMAKE_COMMAND) -P CMakeFiles/open62541-generator-ns-example.dir/cmake_clean.cmake
.PHONY : nodeset/CMakeFiles/open62541-generator-ns-example.dir/clean

nodeset/CMakeFiles/open62541-generator-ns-example.dir/depend:
	cd /home/elkmir/work/open62541/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples/nodeset /home/elkmir/work/open62541/examples /home/elkmir/work/open62541/examples/nodeset /home/elkmir/work/open62541/examples/nodeset/CMakeFiles/open62541-generator-ns-example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : nodeset/CMakeFiles/open62541-generator-ns-example.dir/depend

