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

# Utility rule file for openocd.

# Include the progress variables for this target.
include CMakeFiles/openocd.dir/progress.make

CMakeFiles/openocd:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/andi/git/inav/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Run openocd using OPENOCD_CFG=() as configuration"
	/mnt/c/Users/andi__000/AppData/Roaming/xPacks/@gnu-mcu-eclipse/openocd/0.10.0-11.1/.content/bin/openocd.exe -f

openocd: CMakeFiles/openocd
openocd: CMakeFiles/openocd.dir/build.make

.PHONY : openocd

# Rule to build all files generated by this target.
CMakeFiles/openocd.dir/build: openocd

.PHONY : CMakeFiles/openocd.dir/build

CMakeFiles/openocd.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/openocd.dir/cmake_clean.cmake
.PHONY : CMakeFiles/openocd.dir/clean

CMakeFiles/openocd.dir/depend:
	cd /home/andi/git/inav/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andi/git/inav /home/andi/git/inav /home/andi/git/inav/release /home/andi/git/inav/release /home/andi/git/inav/release/CMakeFiles/openocd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/openocd.dir/depend

