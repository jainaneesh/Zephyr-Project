# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspace/apps/multiple_esp_comm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspace/apps/multiple_esp_comm/build

# Utility rule file for debug.

# Include any custom commands dependencies for this target.
include zephyr/cmake/flash/CMakeFiles/debug.dir/compiler_depend.make

# Include the progress variables for this target.
include zephyr/cmake/flash/CMakeFiles/debug.dir/progress.make

zephyr/cmake/flash/CMakeFiles/debug:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/workspace/apps/multiple_esp_comm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Debugging esp32s3_devkitc"
	/usr/bin/cmake -DTARGET=debug -DDEPENDENCIES="" -P /opt/toolchains/zephyr/cmake/flash/check_runner_dependencies.cmake
	/usr/bin/cmake -E env /opt/venv/bin/python3 -m west debug

debug: zephyr/cmake/flash/CMakeFiles/debug
debug: zephyr/cmake/flash/CMakeFiles/debug.dir/build.make
.PHONY : debug

# Rule to build all files generated by this target.
zephyr/cmake/flash/CMakeFiles/debug.dir/build: debug
.PHONY : zephyr/cmake/flash/CMakeFiles/debug.dir/build

zephyr/cmake/flash/CMakeFiles/debug.dir/clean:
	cd /workspace/apps/multiple_esp_comm/build/zephyr/cmake/flash && $(CMAKE_COMMAND) -P CMakeFiles/debug.dir/cmake_clean.cmake
.PHONY : zephyr/cmake/flash/CMakeFiles/debug.dir/clean

zephyr/cmake/flash/CMakeFiles/debug.dir/depend:
	cd /workspace/apps/multiple_esp_comm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspace/apps/multiple_esp_comm /opt/toolchains/zephyr/cmake/flash /workspace/apps/multiple_esp_comm/build /workspace/apps/multiple_esp_comm/build/zephyr/cmake/flash /workspace/apps/multiple_esp_comm/build/zephyr/cmake/flash/CMakeFiles/debug.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/cmake/flash/CMakeFiles/debug.dir/depend

