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

# Utility rule file for FOXEERF722DUAL_bl.

# Include the progress variables for this target.
include src/main/target/FOXEERF722DUAL/CMakeFiles/FOXEERF722DUAL_bl.dir/progress.make

src/main/target/FOXEERF722DUAL/CMakeFiles/FOXEERF722DUAL_bl:
	cd /home/andi/git/inav/debug/src/main/target/FOXEERF722DUAL && cmake -E env PATH=/home/andi/git/inav/tools/gcc-arm-none-eabi-10-2020-q4-major/bin:/home/andi/.vscode-server/bin/b3318bc0524af3d74034b8bb8a64df0ccf35549a/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Users/andi__000/AppData/Roaming/xPacks/@gnu-mcu-eclipse/openocd/0.10.0-11.1/.content/bin:/snap/bin arm-none-eabi-objcopy -Oihex --set-start 0x08000000 /home/andi/git/inav/debug/bin/FOXEERF722DUAL_bl.elf /home/andi/git/inav/debug/inav_3.1.0_FOXEERF722DUAL_bl.hex

FOXEERF722DUAL_bl: src/main/target/FOXEERF722DUAL/CMakeFiles/FOXEERF722DUAL_bl
FOXEERF722DUAL_bl: src/main/target/FOXEERF722DUAL/CMakeFiles/FOXEERF722DUAL_bl.dir/build.make

.PHONY : FOXEERF722DUAL_bl

# Rule to build all files generated by this target.
src/main/target/FOXEERF722DUAL/CMakeFiles/FOXEERF722DUAL_bl.dir/build: FOXEERF722DUAL_bl

.PHONY : src/main/target/FOXEERF722DUAL/CMakeFiles/FOXEERF722DUAL_bl.dir/build

src/main/target/FOXEERF722DUAL/CMakeFiles/FOXEERF722DUAL_bl.dir/clean:
	cd /home/andi/git/inav/debug/src/main/target/FOXEERF722DUAL && $(CMAKE_COMMAND) -P CMakeFiles/FOXEERF722DUAL_bl.dir/cmake_clean.cmake
.PHONY : src/main/target/FOXEERF722DUAL/CMakeFiles/FOXEERF722DUAL_bl.dir/clean

src/main/target/FOXEERF722DUAL/CMakeFiles/FOXEERF722DUAL_bl.dir/depend:
	cd /home/andi/git/inav/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andi/git/inav /home/andi/git/inav/src/main/target/FOXEERF722DUAL /home/andi/git/inav/debug /home/andi/git/inav/debug/src/main/target/FOXEERF722DUAL /home/andi/git/inav/debug/src/main/target/FOXEERF722DUAL/CMakeFiles/FOXEERF722DUAL_bl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/main/target/FOXEERF722DUAL/CMakeFiles/FOXEERF722DUAL_bl.dir/depend

