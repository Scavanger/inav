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
CMAKE_BINARY_DIR = /home/andi/git/inav/debug

# Utility rule file for FF_PIKOF4_with_bl.

# Include the progress variables for this target.
include src/main/target/FF_PIKOF4/CMakeFiles/FF_PIKOF4_with_bl.dir/progress.make

src/main/target/FF_PIKOF4/CMakeFiles/FF_PIKOF4_with_bl:
	cd /home/andi/git/inav/debug/src/main/target/FF_PIKOF4 && ../../../../../src/utils/combine_tool /home/andi/git/inav/debug/inav_3.1.0_FF_PIKOF4_bl.bin /home/andi/git/inav/debug/inav_3.1.0_FF_PIKOF4_for_bl.bin /home/andi/git/inav/debug/inav_3.1.0_FF_PIKOF4_with_bl.hex

FF_PIKOF4_with_bl: src/main/target/FF_PIKOF4/CMakeFiles/FF_PIKOF4_with_bl
FF_PIKOF4_with_bl: src/main/target/FF_PIKOF4/CMakeFiles/FF_PIKOF4_with_bl.dir/build.make

.PHONY : FF_PIKOF4_with_bl

# Rule to build all files generated by this target.
src/main/target/FF_PIKOF4/CMakeFiles/FF_PIKOF4_with_bl.dir/build: FF_PIKOF4_with_bl

.PHONY : src/main/target/FF_PIKOF4/CMakeFiles/FF_PIKOF4_with_bl.dir/build

src/main/target/FF_PIKOF4/CMakeFiles/FF_PIKOF4_with_bl.dir/clean:
	cd /home/andi/git/inav/debug/src/main/target/FF_PIKOF4 && $(CMAKE_COMMAND) -P CMakeFiles/FF_PIKOF4_with_bl.dir/cmake_clean.cmake
.PHONY : src/main/target/FF_PIKOF4/CMakeFiles/FF_PIKOF4_with_bl.dir/clean

src/main/target/FF_PIKOF4/CMakeFiles/FF_PIKOF4_with_bl.dir/depend:
	cd /home/andi/git/inav/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andi/git/inav /home/andi/git/inav/src/main/target/FF_PIKOF4 /home/andi/git/inav/debug /home/andi/git/inav/debug/src/main/target/FF_PIKOF4 /home/andi/git/inav/debug/src/main/target/FF_PIKOF4/CMakeFiles/FF_PIKOF4_with_bl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/main/target/FF_PIKOF4/CMakeFiles/FF_PIKOF4_with_bl.dir/depend

