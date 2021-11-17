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

# Utility rule file for openocd_FLYWOOF7DUAL.

# Include the progress variables for this target.
include src/main/target/FLYWOOF7DUAL/CMakeFiles/openocd_FLYWOOF7DUAL.dir/progress.make

src/main/target/FLYWOOF7DUAL/CMakeFiles/openocd_FLYWOOF7DUAL: openocd/FLYWOOF7DUAL.cfg
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/andi/git/inav/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running openocd for target FLYWOOF7DUAL via stlink"
	cd /home/andi/git/inav/debug/src/main/target/FLYWOOF7DUAL && /mnt/c/Users/andi__000/AppData/Roaming/xPacks/@gnu-mcu-eclipse/openocd/0.10.0-11.1/.content/bin/openocd.exe -f /home/andi/git/inav/debug/openocd/FLYWOOF7DUAL.cfg

openocd/FLYWOOF7DUAL.cfg:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/andi/git/inav/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating openocd configuration for stm32f7x via stlink"
	cd /home/andi/git/inav/debug/src/main/target/FLYWOOF7DUAL && /usr/local/bin/cmake -P /home/andi/git/inav/cmake/openocd_cfg.cmake stm32f7x stlink /home/andi/git/inav/debug/openocd/FLYWOOF7DUAL.cfg

openocd_FLYWOOF7DUAL: src/main/target/FLYWOOF7DUAL/CMakeFiles/openocd_FLYWOOF7DUAL
openocd_FLYWOOF7DUAL: openocd/FLYWOOF7DUAL.cfg
openocd_FLYWOOF7DUAL: src/main/target/FLYWOOF7DUAL/CMakeFiles/openocd_FLYWOOF7DUAL.dir/build.make

.PHONY : openocd_FLYWOOF7DUAL

# Rule to build all files generated by this target.
src/main/target/FLYWOOF7DUAL/CMakeFiles/openocd_FLYWOOF7DUAL.dir/build: openocd_FLYWOOF7DUAL

.PHONY : src/main/target/FLYWOOF7DUAL/CMakeFiles/openocd_FLYWOOF7DUAL.dir/build

src/main/target/FLYWOOF7DUAL/CMakeFiles/openocd_FLYWOOF7DUAL.dir/clean:
	cd /home/andi/git/inav/debug/src/main/target/FLYWOOF7DUAL && $(CMAKE_COMMAND) -P CMakeFiles/openocd_FLYWOOF7DUAL.dir/cmake_clean.cmake
.PHONY : src/main/target/FLYWOOF7DUAL/CMakeFiles/openocd_FLYWOOF7DUAL.dir/clean

src/main/target/FLYWOOF7DUAL/CMakeFiles/openocd_FLYWOOF7DUAL.dir/depend:
	cd /home/andi/git/inav/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andi/git/inav /home/andi/git/inav/src/main/target/FLYWOOF7DUAL /home/andi/git/inav/debug /home/andi/git/inav/debug/src/main/target/FLYWOOF7DUAL /home/andi/git/inav/debug/src/main/target/FLYWOOF7DUAL/CMakeFiles/openocd_FLYWOOF7DUAL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/main/target/FLYWOOF7DUAL/CMakeFiles/openocd_FLYWOOF7DUAL.dir/depend

