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

# Utility rule file for svd_ALIENFLIGHTF3.

# Include the progress variables for this target.
include src/main/target/ALIENFLIGHTF3/CMakeFiles/svd_ALIENFLIGHTF3.dir/progress.make

src/main/target/ALIENFLIGHTF3/CMakeFiles/svd_ALIENFLIGHTF3:
	cd /home/andi/git/inav/release/src/main/target/ALIENFLIGHTF3 && /usr/local/bin/cmake -E copy /home/andi/git/inav/dev/svd/STM32F303.svd /home/andi/git/inav/release/svd/ALIENFLIGHTF3.svd

svd_ALIENFLIGHTF3: src/main/target/ALIENFLIGHTF3/CMakeFiles/svd_ALIENFLIGHTF3
svd_ALIENFLIGHTF3: src/main/target/ALIENFLIGHTF3/CMakeFiles/svd_ALIENFLIGHTF3.dir/build.make

.PHONY : svd_ALIENFLIGHTF3

# Rule to build all files generated by this target.
src/main/target/ALIENFLIGHTF3/CMakeFiles/svd_ALIENFLIGHTF3.dir/build: svd_ALIENFLIGHTF3

.PHONY : src/main/target/ALIENFLIGHTF3/CMakeFiles/svd_ALIENFLIGHTF3.dir/build

src/main/target/ALIENFLIGHTF3/CMakeFiles/svd_ALIENFLIGHTF3.dir/clean:
	cd /home/andi/git/inav/release/src/main/target/ALIENFLIGHTF3 && $(CMAKE_COMMAND) -P CMakeFiles/svd_ALIENFLIGHTF3.dir/cmake_clean.cmake
.PHONY : src/main/target/ALIENFLIGHTF3/CMakeFiles/svd_ALIENFLIGHTF3.dir/clean

src/main/target/ALIENFLIGHTF3/CMakeFiles/svd_ALIENFLIGHTF3.dir/depend:
	cd /home/andi/git/inav/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andi/git/inav /home/andi/git/inav/src/main/target/ALIENFLIGHTF3 /home/andi/git/inav/release /home/andi/git/inav/release/src/main/target/ALIENFLIGHTF3 /home/andi/git/inav/release/src/main/target/ALIENFLIGHTF3/CMakeFiles/svd_ALIENFLIGHTF3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/main/target/ALIENFLIGHTF3/CMakeFiles/svd_ALIENFLIGHTF3.dir/depend

