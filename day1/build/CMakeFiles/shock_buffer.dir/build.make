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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/analog/Documents/iio-apps-2023/day1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/analog/Documents/iio-apps-2023/day1/build

# Include any dependencies generated for this target.
include CMakeFiles/shock_buffer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/shock_buffer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shock_buffer.dir/flags.make

CMakeFiles/shock_buffer.dir/shock_buffer.c.o: CMakeFiles/shock_buffer.dir/flags.make
CMakeFiles/shock_buffer.dir/shock_buffer.c.o: ../shock_buffer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/analog/Documents/iio-apps-2023/day1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/shock_buffer.dir/shock_buffer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shock_buffer.dir/shock_buffer.c.o -c /home/analog/Documents/iio-apps-2023/day1/shock_buffer.c

CMakeFiles/shock_buffer.dir/shock_buffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shock_buffer.dir/shock_buffer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/analog/Documents/iio-apps-2023/day1/shock_buffer.c > CMakeFiles/shock_buffer.dir/shock_buffer.c.i

CMakeFiles/shock_buffer.dir/shock_buffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shock_buffer.dir/shock_buffer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/analog/Documents/iio-apps-2023/day1/shock_buffer.c -o CMakeFiles/shock_buffer.dir/shock_buffer.c.s

# Object files for target shock_buffer
shock_buffer_OBJECTS = \
"CMakeFiles/shock_buffer.dir/shock_buffer.c.o"

# External object files for target shock_buffer
shock_buffer_EXTERNAL_OBJECTS =

shock_buffer: CMakeFiles/shock_buffer.dir/shock_buffer.c.o
shock_buffer: CMakeFiles/shock_buffer.dir/build.make
shock_buffer: CMakeFiles/shock_buffer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/analog/Documents/iio-apps-2023/day1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable shock_buffer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shock_buffer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shock_buffer.dir/build: shock_buffer

.PHONY : CMakeFiles/shock_buffer.dir/build

CMakeFiles/shock_buffer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shock_buffer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shock_buffer.dir/clean

CMakeFiles/shock_buffer.dir/depend:
	cd /home/analog/Documents/iio-apps-2023/day1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/analog/Documents/iio-apps-2023/day1 /home/analog/Documents/iio-apps-2023/day1 /home/analog/Documents/iio-apps-2023/day1/build /home/analog/Documents/iio-apps-2023/day1/build /home/analog/Documents/iio-apps-2023/day1/build/CMakeFiles/shock_buffer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shock_buffer.dir/depend

