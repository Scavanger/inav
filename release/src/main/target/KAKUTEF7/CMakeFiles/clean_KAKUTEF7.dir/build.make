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

# Utility rule file for clean_KAKUTEF7.

# Include the progress variables for this target.
include src/main/target/KAKUTEF7/CMakeFiles/clean_KAKUTEF7.dir/progress.make

src/main/target/KAKUTEF7/CMakeFiles/clean_KAKUTEF7:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/andi/git/inav/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Removing intermediate files for KAKUTEF7"
	make clean

clean_KAKUTEF7: src/main/target/KAKUTEF7/CMakeFiles/clean_KAKUTEF7
clean_KAKUTEF7: src/main/target/KAKUTEF7/CMakeFiles/clean_KAKUTEF7.dir/build.make

.PHONY : clean_KAKUTEF7

# Rule to build all files generated by this target.
src/main/target/KAKUTEF7/CMakeFiles/clean_KAKUTEF7.dir/build: clean_KAKUTEF7

.PHONY : src/main/target/KAKUTEF7/CMakeFiles/clean_KAKUTEF7.dir/build

src/main/target/KAKUTEF7/CMakeFiles/clean_KAKUTEF7.dir/clean:
	cd /home/andi/git/inav/release/src/main/target/KAKUTEF7 && $(CMAKE_COMMAND) -P CMakeFiles/clean_KAKUTEF7.dir/cmake_clean.cmake
.PHONY : src/main/target/KAKUTEF7/CMakeFiles/clean_KAKUTEF7.dir/clean

src/main/target/KAKUTEF7/CMakeFiles/clean_KAKUTEF7.dir/depend:
	cd /home/andi/git/inav/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andi/git/inav /home/andi/git/inav/src/main/target/KAKUTEF7 /home/andi/git/inav/release /home/andi/git/inav/release/src/main/target/KAKUTEF7 /home/andi/git/inav/release/src/main/target/KAKUTEF7/CMakeFiles/clean_KAKUTEF7.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/main/target/KAKUTEF7/CMakeFiles/clean_KAKUTEF7.dir/depend

