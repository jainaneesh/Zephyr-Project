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

# Utility rule file for rom_report.

# Include any custom commands dependencies for this target.
include zephyr/cmake/reports/CMakeFiles/rom_report.dir/compiler_depend.make

# Include the progress variables for this target.
include zephyr/cmake/reports/CMakeFiles/rom_report.dir/progress.make

zephyr/cmake/reports/CMakeFiles/rom_report: zephyr/zephyr.elf
	/opt/venv/bin/python3 /opt/toolchains/zephyr/scripts/footprint/size_report -k /workspace/apps/multiple_esp_comm/build/zephyr/zephyr.elf -z /opt/toolchains/zephyr -o /workspace/apps/multiple_esp_comm/build --workspace=/opt/toolchains -d 99 rom

rom_report: zephyr/cmake/reports/CMakeFiles/rom_report
rom_report: zephyr/cmake/reports/CMakeFiles/rom_report.dir/build.make
.PHONY : rom_report

# Rule to build all files generated by this target.
zephyr/cmake/reports/CMakeFiles/rom_report.dir/build: rom_report
.PHONY : zephyr/cmake/reports/CMakeFiles/rom_report.dir/build

zephyr/cmake/reports/CMakeFiles/rom_report.dir/clean:
	cd /workspace/apps/multiple_esp_comm/build/zephyr/cmake/reports && $(CMAKE_COMMAND) -P CMakeFiles/rom_report.dir/cmake_clean.cmake
.PHONY : zephyr/cmake/reports/CMakeFiles/rom_report.dir/clean

zephyr/cmake/reports/CMakeFiles/rom_report.dir/depend:
	cd /workspace/apps/multiple_esp_comm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspace/apps/multiple_esp_comm /opt/toolchains/zephyr/cmake/reports /workspace/apps/multiple_esp_comm/build /workspace/apps/multiple_esp_comm/build/zephyr/cmake/reports /workspace/apps/multiple_esp_comm/build/zephyr/cmake/reports/CMakeFiles/rom_report.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/cmake/reports/CMakeFiles/rom_report.dir/depend

