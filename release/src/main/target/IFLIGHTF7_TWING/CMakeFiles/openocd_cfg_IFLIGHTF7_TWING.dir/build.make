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

# Utility rule file for openocd_cfg_IFLIGHTF7_TWING.

# Include the progress variables for this target.
include src/main/target/IFLIGHTF7_TWING/CMakeFiles/openocd_cfg_IFLIGHTF7_TWING.dir/progress.make

src/main/target/IFLIGHTF7_TWING/CMakeFiles/openocd_cfg_IFLIGHTF7_TWING: openocd/IFLIGHTF7_TWING.cfg


openocd/IFLIGHTF7_TWING.cfg:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/andi/git/inav/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating openocd configuration for stm32f7x via stlink"
	cd /home/andi/git/inav/release/src/main/target/IFLIGHTF7_TWING && /usr/local/bin/cmake -P /home/andi/git/inav/cmake/openocd_cfg.cmake stm32f7x stlink /home/andi/git/inav/release/openocd/IFLIGHTF7_TWING.cfg

openocd_cfg_IFLIGHTF7_TWING: src/main/target/IFLIGHTF7_TWING/CMakeFiles/openocd_cfg_IFLIGHTF7_TWING
openocd_cfg_IFLIGHTF7_TWING: openocd/IFLIGHTF7_TWING.cfg
openocd_cfg_IFLIGHTF7_TWING: src/main/target/IFLIGHTF7_TWING/CMakeFiles/openocd_cfg_IFLIGHTF7_TWING.dir/build.make

.PHONY : openocd_cfg_IFLIGHTF7_TWING

# Rule to build all files generated by this target.
src/main/target/IFLIGHTF7_TWING/CMakeFiles/openocd_cfg_IFLIGHTF7_TWING.dir/build: openocd_cfg_IFLIGHTF7_TWING

.PHONY : src/main/target/IFLIGHTF7_TWING/CMakeFiles/openocd_cfg_IFLIGHTF7_TWING.dir/build

src/main/target/IFLIGHTF7_TWING/CMakeFiles/openocd_cfg_IFLIGHTF7_TWING.dir/clean:
	cd /home/andi/git/inav/release/src/main/target/IFLIGHTF7_TWING && $(CMAKE_COMMAND) -P CMakeFiles/openocd_cfg_IFLIGHTF7_TWING.dir/cmake_clean.cmake
.PHONY : src/main/target/IFLIGHTF7_TWING/CMakeFiles/openocd_cfg_IFLIGHTF7_TWING.dir/clean

src/main/target/IFLIGHTF7_TWING/CMakeFiles/openocd_cfg_IFLIGHTF7_TWING.dir/depend:
	cd /home/andi/git/inav/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andi/git/inav /home/andi/git/inav/src/main/target/IFLIGHTF7_TWING /home/andi/git/inav/release /home/andi/git/inav/release/src/main/target/IFLIGHTF7_TWING /home/andi/git/inav/release/src/main/target/IFLIGHTF7_TWING/CMakeFiles/openocd_cfg_IFLIGHTF7_TWING.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/main/target/IFLIGHTF7_TWING/CMakeFiles/openocd_cfg_IFLIGHTF7_TWING.dir/depend

