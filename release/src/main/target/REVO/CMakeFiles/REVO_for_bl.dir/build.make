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

# Utility rule file for REVO_for_bl.

# Include the progress variables for this target.
include src/main/target/REVO/CMakeFiles/REVO_for_bl.dir/progress.make

src/main/target/REVO/CMakeFiles/REVO_for_bl:
	cd /home/andi/git/inav/release/src/main/target/REVO && cmake -E env PATH=/home/andi/git/inav/tools/gcc-arm-none-eabi-10-2020-q4-major/bin:/home/andi/.vscode-server/bin/7f6ab5485bbc008386c4386d08766667e155244e/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Users/andi__000/AppData/Roaming/xPacks/@gnu-mcu-eclipse/openocd/0.10.0-11.1/.content/bin:/snap/bin arm-none-eabi-objcopy -Oihex --set-start 0x08000000 /home/andi/git/inav/release/bin/REVO_for_bl.elf /home/andi/git/inav/release/inav_3.1.0_REVO_for_bl.hex

REVO_for_bl: src/main/target/REVO/CMakeFiles/REVO_for_bl
REVO_for_bl: src/main/target/REVO/CMakeFiles/REVO_for_bl.dir/build.make

.PHONY : REVO_for_bl

# Rule to build all files generated by this target.
src/main/target/REVO/CMakeFiles/REVO_for_bl.dir/build: REVO_for_bl

.PHONY : src/main/target/REVO/CMakeFiles/REVO_for_bl.dir/build

src/main/target/REVO/CMakeFiles/REVO_for_bl.dir/clean:
	cd /home/andi/git/inav/release/src/main/target/REVO && $(CMAKE_COMMAND) -P CMakeFiles/REVO_for_bl.dir/cmake_clean.cmake
.PHONY : src/main/target/REVO/CMakeFiles/REVO_for_bl.dir/clean

src/main/target/REVO/CMakeFiles/REVO_for_bl.dir/depend:
	cd /home/andi/git/inav/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andi/git/inav /home/andi/git/inav/src/main/target/REVO /home/andi/git/inav/release /home/andi/git/inav/release/src/main/target/REVO /home/andi/git/inav/release/src/main/target/REVO/CMakeFiles/REVO_for_bl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/main/target/REVO/CMakeFiles/REVO_for_bl.dir/depend

