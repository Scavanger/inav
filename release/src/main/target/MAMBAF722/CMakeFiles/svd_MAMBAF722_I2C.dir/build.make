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

# Utility rule file for svd_MAMBAF722_I2C.

# Include the progress variables for this target.
include src/main/target/MAMBAF722/CMakeFiles/svd_MAMBAF722_I2C.dir/progress.make

src/main/target/MAMBAF722/CMakeFiles/svd_MAMBAF722_I2C:
	cd /home/andi/git/inav/release/src/main/target/MAMBAF722 && /usr/local/bin/cmake -E echo target\ MAMBAF722_I2C\ does\ not\ declare\ an\ SVD\ filename
	cd /home/andi/git/inav/release/src/main/target/MAMBAF722 && /usr/local/bin/cmake -E false

svd_MAMBAF722_I2C: src/main/target/MAMBAF722/CMakeFiles/svd_MAMBAF722_I2C
svd_MAMBAF722_I2C: src/main/target/MAMBAF722/CMakeFiles/svd_MAMBAF722_I2C.dir/build.make

.PHONY : svd_MAMBAF722_I2C

# Rule to build all files generated by this target.
src/main/target/MAMBAF722/CMakeFiles/svd_MAMBAF722_I2C.dir/build: svd_MAMBAF722_I2C

.PHONY : src/main/target/MAMBAF722/CMakeFiles/svd_MAMBAF722_I2C.dir/build

src/main/target/MAMBAF722/CMakeFiles/svd_MAMBAF722_I2C.dir/clean:
	cd /home/andi/git/inav/release/src/main/target/MAMBAF722 && $(CMAKE_COMMAND) -P CMakeFiles/svd_MAMBAF722_I2C.dir/cmake_clean.cmake
.PHONY : src/main/target/MAMBAF722/CMakeFiles/svd_MAMBAF722_I2C.dir/clean

src/main/target/MAMBAF722/CMakeFiles/svd_MAMBAF722_I2C.dir/depend:
	cd /home/andi/git/inav/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andi/git/inav /home/andi/git/inav/src/main/target/MAMBAF722 /home/andi/git/inav/release /home/andi/git/inav/release/src/main/target/MAMBAF722 /home/andi/git/inav/release/src/main/target/MAMBAF722/CMakeFiles/svd_MAMBAF722_I2C.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/main/target/MAMBAF722/CMakeFiles/svd_MAMBAF722_I2C.dir/depend

