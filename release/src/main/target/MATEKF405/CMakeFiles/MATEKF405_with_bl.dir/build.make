# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/andi/git/inav

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andi/git/inav/release

# Utility rule file for MATEKF405_with_bl.

# Include the progress variables for this target.
include src/main/target/MATEKF405/CMakeFiles/MATEKF405_with_bl.dir/progress.make

src/main/target/MATEKF405/CMakeFiles/MATEKF405_with_bl:
	cd /home/andi/git/inav/release/src/main/target/MATEKF405 && ../../../../../src/utils/combine_tool /home/andi/git/inav/release/inav_3.1.0_MATEKF405_bl.bin /home/andi/git/inav/release/inav_3.1.0_MATEKF405_for_bl.bin /home/andi/git/inav/release/inav_3.1.0_MATEKF405_with_bl.hex

MATEKF405_with_bl: src/main/target/MATEKF405/CMakeFiles/MATEKF405_with_bl
MATEKF405_with_bl: src/main/target/MATEKF405/CMakeFiles/MATEKF405_with_bl.dir/build.make

.PHONY : MATEKF405_with_bl

# Rule to build all files generated by this target.
src/main/target/MATEKF405/CMakeFiles/MATEKF405_with_bl.dir/build: MATEKF405_with_bl

.PHONY : src/main/target/MATEKF405/CMakeFiles/MATEKF405_with_bl.dir/build

src/main/target/MATEKF405/CMakeFiles/MATEKF405_with_bl.dir/clean:
	cd /home/andi/git/inav/release/src/main/target/MATEKF405 && $(CMAKE_COMMAND) -P CMakeFiles/MATEKF405_with_bl.dir/cmake_clean.cmake
.PHONY : src/main/target/MATEKF405/CMakeFiles/MATEKF405_with_bl.dir/clean

src/main/target/MATEKF405/CMakeFiles/MATEKF405_with_bl.dir/depend:
	cd /home/andi/git/inav/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andi/git/inav /home/andi/git/inav/src/main/target/MATEKF405 /home/andi/git/inav/release /home/andi/git/inav/release/src/main/target/MATEKF405 /home/andi/git/inav/release/src/main/target/MATEKF405/CMakeFiles/MATEKF405_with_bl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/main/target/MATEKF405/CMakeFiles/MATEKF405_with_bl.dir/depend

