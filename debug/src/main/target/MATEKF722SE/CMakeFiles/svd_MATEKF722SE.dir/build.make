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

# Utility rule file for svd_MATEKF722SE.

# Include the progress variables for this target.
include src/main/target/MATEKF722SE/CMakeFiles/svd_MATEKF722SE.dir/progress.make

src/main/target/MATEKF722SE/CMakeFiles/svd_MATEKF722SE:
	cd /home/andi/git/inav/debug/src/main/target/MATEKF722SE && /usr/local/bin/cmake -E echo target\ MATEKF722SE\ does\ not\ declare\ an\ SVD\ filename
	cd /home/andi/git/inav/debug/src/main/target/MATEKF722SE && /usr/local/bin/cmake -E false

svd_MATEKF722SE: src/main/target/MATEKF722SE/CMakeFiles/svd_MATEKF722SE
svd_MATEKF722SE: src/main/target/MATEKF722SE/CMakeFiles/svd_MATEKF722SE.dir/build.make

.PHONY : svd_MATEKF722SE

# Rule to build all files generated by this target.
src/main/target/MATEKF722SE/CMakeFiles/svd_MATEKF722SE.dir/build: svd_MATEKF722SE

.PHONY : src/main/target/MATEKF722SE/CMakeFiles/svd_MATEKF722SE.dir/build

src/main/target/MATEKF722SE/CMakeFiles/svd_MATEKF722SE.dir/clean:
	cd /home/andi/git/inav/debug/src/main/target/MATEKF722SE && $(CMAKE_COMMAND) -P CMakeFiles/svd_MATEKF722SE.dir/cmake_clean.cmake
.PHONY : src/main/target/MATEKF722SE/CMakeFiles/svd_MATEKF722SE.dir/clean

src/main/target/MATEKF722SE/CMakeFiles/svd_MATEKF722SE.dir/depend:
	cd /home/andi/git/inav/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andi/git/inav /home/andi/git/inav/src/main/target/MATEKF722SE /home/andi/git/inav/debug /home/andi/git/inav/debug/src/main/target/MATEKF722SE /home/andi/git/inav/debug/src/main/target/MATEKF722SE/CMakeFiles/svd_MATEKF722SE.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/main/target/MATEKF722SE/CMakeFiles/svd_MATEKF722SE.dir/depend

