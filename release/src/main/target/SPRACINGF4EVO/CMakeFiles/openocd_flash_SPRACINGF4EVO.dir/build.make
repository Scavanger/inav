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

# Utility rule file for openocd_flash_SPRACINGF4EVO.

# Include the progress variables for this target.
include src/main/target/SPRACINGF4EVO/CMakeFiles/openocd_flash_SPRACINGF4EVO.dir/progress.make

src/main/target/SPRACINGF4EVO/CMakeFiles/openocd_flash_SPRACINGF4EVO: openocd/SPRACINGF4EVO.cfg
src/main/target/SPRACINGF4EVO/CMakeFiles/openocd_flash_SPRACINGF4EVO: bin/SPRACINGF4EVO.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/andi/git/inav/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Flashing SPRACINGF4EVO with openocd"
	cd /home/andi/git/inav/release/src/main/target/SPRACINGF4EVO && /usr/local/bin/cmake -E env OPENOCD_CMD=/mnt/c/Users/andi__000/AppData/Roaming/xPacks/@gnu-mcu-eclipse/openocd/0.10.0-11.1/.content/bin/openocd.exe /home/andi/git/inav/src/utils/openocd_flash.py -f /home/andi/git/inav/release/openocd/SPRACINGF4EVO.cfg /home/andi/git/inav/release/bin/SPRACINGF4EVO.elf

openocd/SPRACINGF4EVO.cfg:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/andi/git/inav/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating openocd configuration for stm32f4x via stlink"
	cd /home/andi/git/inav/release/src/main/target/SPRACINGF4EVO && /usr/local/bin/cmake -P /home/andi/git/inav/cmake/openocd_cfg.cmake stm32f4x stlink /home/andi/git/inav/release/openocd/SPRACINGF4EVO.cfg

openocd_flash_SPRACINGF4EVO: src/main/target/SPRACINGF4EVO/CMakeFiles/openocd_flash_SPRACINGF4EVO
openocd_flash_SPRACINGF4EVO: openocd/SPRACINGF4EVO.cfg
openocd_flash_SPRACINGF4EVO: src/main/target/SPRACINGF4EVO/CMakeFiles/openocd_flash_SPRACINGF4EVO.dir/build.make

.PHONY : openocd_flash_SPRACINGF4EVO

# Rule to build all files generated by this target.
src/main/target/SPRACINGF4EVO/CMakeFiles/openocd_flash_SPRACINGF4EVO.dir/build: openocd_flash_SPRACINGF4EVO

.PHONY : src/main/target/SPRACINGF4EVO/CMakeFiles/openocd_flash_SPRACINGF4EVO.dir/build

src/main/target/SPRACINGF4EVO/CMakeFiles/openocd_flash_SPRACINGF4EVO.dir/clean:
	cd /home/andi/git/inav/release/src/main/target/SPRACINGF4EVO && $(CMAKE_COMMAND) -P CMakeFiles/openocd_flash_SPRACINGF4EVO.dir/cmake_clean.cmake
.PHONY : src/main/target/SPRACINGF4EVO/CMakeFiles/openocd_flash_SPRACINGF4EVO.dir/clean

src/main/target/SPRACINGF4EVO/CMakeFiles/openocd_flash_SPRACINGF4EVO.dir/depend:
	cd /home/andi/git/inav/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andi/git/inav /home/andi/git/inav/src/main/target/SPRACINGF4EVO /home/andi/git/inav/release /home/andi/git/inav/release/src/main/target/SPRACINGF4EVO /home/andi/git/inav/release/src/main/target/SPRACINGF4EVO/CMakeFiles/openocd_flash_SPRACINGF4EVO.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/main/target/SPRACINGF4EVO/CMakeFiles/openocd_flash_SPRACINGF4EVO.dir/depend

