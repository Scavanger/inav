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

# Utility rule file for openocd_cfg_OMNIBUSF4V3_S5S6_SS.

# Include the progress variables for this target.
include src/main/target/OMNIBUSF4/CMakeFiles/openocd_cfg_OMNIBUSF4V3_S5S6_SS.dir/progress.make

src/main/target/OMNIBUSF4/CMakeFiles/openocd_cfg_OMNIBUSF4V3_S5S6_SS: openocd/OMNIBUSF4V3_S5S6_SS.cfg


openocd/OMNIBUSF4V3_S5S6_SS.cfg:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/andi/git/inav/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating openocd configuration for stm32f4x via stlink"
	cd /home/andi/git/inav/debug/src/main/target/OMNIBUSF4 && /usr/local/bin/cmake -P /home/andi/git/inav/cmake/openocd_cfg.cmake stm32f4x stlink /home/andi/git/inav/debug/openocd/OMNIBUSF4V3_S5S6_SS.cfg

openocd_cfg_OMNIBUSF4V3_S5S6_SS: src/main/target/OMNIBUSF4/CMakeFiles/openocd_cfg_OMNIBUSF4V3_S5S6_SS
openocd_cfg_OMNIBUSF4V3_S5S6_SS: openocd/OMNIBUSF4V3_S5S6_SS.cfg
openocd_cfg_OMNIBUSF4V3_S5S6_SS: src/main/target/OMNIBUSF4/CMakeFiles/openocd_cfg_OMNIBUSF4V3_S5S6_SS.dir/build.make

.PHONY : openocd_cfg_OMNIBUSF4V3_S5S6_SS

# Rule to build all files generated by this target.
src/main/target/OMNIBUSF4/CMakeFiles/openocd_cfg_OMNIBUSF4V3_S5S6_SS.dir/build: openocd_cfg_OMNIBUSF4V3_S5S6_SS

.PHONY : src/main/target/OMNIBUSF4/CMakeFiles/openocd_cfg_OMNIBUSF4V3_S5S6_SS.dir/build

src/main/target/OMNIBUSF4/CMakeFiles/openocd_cfg_OMNIBUSF4V3_S5S6_SS.dir/clean:
	cd /home/andi/git/inav/debug/src/main/target/OMNIBUSF4 && $(CMAKE_COMMAND) -P CMakeFiles/openocd_cfg_OMNIBUSF4V3_S5S6_SS.dir/cmake_clean.cmake
.PHONY : src/main/target/OMNIBUSF4/CMakeFiles/openocd_cfg_OMNIBUSF4V3_S5S6_SS.dir/clean

src/main/target/OMNIBUSF4/CMakeFiles/openocd_cfg_OMNIBUSF4V3_S5S6_SS.dir/depend:
	cd /home/andi/git/inav/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andi/git/inav /home/andi/git/inav/src/main/target/OMNIBUSF4 /home/andi/git/inav/debug /home/andi/git/inav/debug/src/main/target/OMNIBUSF4 /home/andi/git/inav/debug/src/main/target/OMNIBUSF4/CMakeFiles/openocd_cfg_OMNIBUSF4V3_S5S6_SS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/main/target/OMNIBUSF4/CMakeFiles/openocd_cfg_OMNIBUSF4V3_S5S6_SS.dir/depend

