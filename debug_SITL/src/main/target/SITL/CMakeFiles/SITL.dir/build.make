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
CMAKE_SOURCE_DIR = /home/andi/git/inav

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andi/git/inav/debug_SITL

# Utility rule file for SITL.

# Include any custom commands dependencies for this target.
include src/main/target/SITL/CMakeFiles/SITL.dir/compiler_depend.make

# Include the progress variables for this target.
include src/main/target/SITL/CMakeFiles/SITL.dir/progress.make

src/main/target/SITL/CMakeFiles/SITL:
	cd /home/andi/git/inav/debug_SITL/src/main/target/SITL && cmake -E copy /home/andi/git/inav/debug_SITL/bin/SITL.elf /home/andi/git/inav/debug_SITL/inav_8.0.0_SITL

SITL: src/main/target/SITL/CMakeFiles/SITL
SITL: src/main/target/SITL/CMakeFiles/SITL.dir/build.make
.PHONY : SITL

# Rule to build all files generated by this target.
src/main/target/SITL/CMakeFiles/SITL.dir/build: SITL
.PHONY : src/main/target/SITL/CMakeFiles/SITL.dir/build

src/main/target/SITL/CMakeFiles/SITL.dir/clean:
	cd /home/andi/git/inav/debug_SITL/src/main/target/SITL && $(CMAKE_COMMAND) -P CMakeFiles/SITL.dir/cmake_clean.cmake
.PHONY : src/main/target/SITL/CMakeFiles/SITL.dir/clean

src/main/target/SITL/CMakeFiles/SITL.dir/depend:
	cd /home/andi/git/inav/debug_SITL && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andi/git/inav /home/andi/git/inav/src/main/target/SITL /home/andi/git/inav/debug_SITL /home/andi/git/inav/debug_SITL/src/main/target/SITL /home/andi/git/inav/debug_SITL/src/main/target/SITL/CMakeFiles/SITL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/main/target/SITL/CMakeFiles/SITL.dir/depend

