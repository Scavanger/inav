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

# Utility rule file for openocd_cfg_F4BY.

# Include the progress variables for this target.
include src/main/target/F4BY/CMakeFiles/openocd_cfg_F4BY.dir/progress.make

src/main/target/F4BY/CMakeFiles/openocd_cfg_F4BY: openocd/F4BY.cfg


openocd/F4BY.cfg:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/andi/git/inav/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating openocd configuration for stm32f4x via stlink"
	cd /home/andi/git/inav/release/src/main/target/F4BY && /usr/local/bin/cmake -P /home/andi/git/inav/cmake/openocd_cfg.cmake stm32f4x stlink /home/andi/git/inav/release/openocd/F4BY.cfg

openocd_cfg_F4BY: src/main/target/F4BY/CMakeFiles/openocd_cfg_F4BY
openocd_cfg_F4BY: openocd/F4BY.cfg
openocd_cfg_F4BY: src/main/target/F4BY/CMakeFiles/openocd_cfg_F4BY.dir/build.make

.PHONY : openocd_cfg_F4BY

# Rule to build all files generated by this target.
src/main/target/F4BY/CMakeFiles/openocd_cfg_F4BY.dir/build: openocd_cfg_F4BY

.PHONY : src/main/target/F4BY/CMakeFiles/openocd_cfg_F4BY.dir/build

src/main/target/F4BY/CMakeFiles/openocd_cfg_F4BY.dir/clean:
	cd /home/andi/git/inav/release/src/main/target/F4BY && $(CMAKE_COMMAND) -P CMakeFiles/openocd_cfg_F4BY.dir/cmake_clean.cmake
.PHONY : src/main/target/F4BY/CMakeFiles/openocd_cfg_F4BY.dir/clean

src/main/target/F4BY/CMakeFiles/openocd_cfg_F4BY.dir/depend:
	cd /home/andi/git/inav/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andi/git/inav /home/andi/git/inav/src/main/target/F4BY /home/andi/git/inav/release /home/andi/git/inav/release/src/main/target/F4BY /home/andi/git/inav/release/src/main/target/F4BY/CMakeFiles/openocd_cfg_F4BY.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/main/target/F4BY/CMakeFiles/openocd_cfg_F4BY.dir/depend

