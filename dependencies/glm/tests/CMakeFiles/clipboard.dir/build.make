# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/jakub/apps/cmake/cmake-3.5.2/bin/cmake

# The command to remove a file.
RM = /home/jakub/apps/cmake/cmake-3.5.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jakub/programming/duck

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jakub/programming/duck

# Include any dependencies generated for this target.
include dependencies/glm/tests/CMakeFiles/clipboard.dir/depend.make

# Include the progress variables for this target.
include dependencies/glm/tests/CMakeFiles/clipboard.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/glm/tests/CMakeFiles/clipboard.dir/flags.make

dependencies/glm/tests/CMakeFiles/clipboard.dir/clipboard.c.o: dependencies/glm/tests/CMakeFiles/clipboard.dir/flags.make
dependencies/glm/tests/CMakeFiles/clipboard.dir/clipboard.c.o: dependencies/glfw-3.1.2/tests/clipboard.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jakub/programming/duck/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dependencies/glm/tests/CMakeFiles/clipboard.dir/clipboard.c.o"
	cd /home/jakub/programming/duck/dependencies/glm/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/clipboard.dir/clipboard.c.o   -c /home/jakub/programming/duck/dependencies/glfw-3.1.2/tests/clipboard.c

dependencies/glm/tests/CMakeFiles/clipboard.dir/clipboard.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clipboard.dir/clipboard.c.i"
	cd /home/jakub/programming/duck/dependencies/glm/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jakub/programming/duck/dependencies/glfw-3.1.2/tests/clipboard.c > CMakeFiles/clipboard.dir/clipboard.c.i

dependencies/glm/tests/CMakeFiles/clipboard.dir/clipboard.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clipboard.dir/clipboard.c.s"
	cd /home/jakub/programming/duck/dependencies/glm/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jakub/programming/duck/dependencies/glfw-3.1.2/tests/clipboard.c -o CMakeFiles/clipboard.dir/clipboard.c.s

dependencies/glm/tests/CMakeFiles/clipboard.dir/clipboard.c.o.requires:

.PHONY : dependencies/glm/tests/CMakeFiles/clipboard.dir/clipboard.c.o.requires

dependencies/glm/tests/CMakeFiles/clipboard.dir/clipboard.c.o.provides: dependencies/glm/tests/CMakeFiles/clipboard.dir/clipboard.c.o.requires
	$(MAKE) -f dependencies/glm/tests/CMakeFiles/clipboard.dir/build.make dependencies/glm/tests/CMakeFiles/clipboard.dir/clipboard.c.o.provides.build
.PHONY : dependencies/glm/tests/CMakeFiles/clipboard.dir/clipboard.c.o.provides

dependencies/glm/tests/CMakeFiles/clipboard.dir/clipboard.c.o.provides.build: dependencies/glm/tests/CMakeFiles/clipboard.dir/clipboard.c.o


dependencies/glm/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.o: dependencies/glm/tests/CMakeFiles/clipboard.dir/flags.make
dependencies/glm/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.o: dependencies/glfw-3.1.2/deps/getopt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jakub/programming/duck/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object dependencies/glm/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.o"
	cd /home/jakub/programming/duck/dependencies/glm/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/clipboard.dir/__/deps/getopt.c.o   -c /home/jakub/programming/duck/dependencies/glfw-3.1.2/deps/getopt.c

dependencies/glm/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clipboard.dir/__/deps/getopt.c.i"
	cd /home/jakub/programming/duck/dependencies/glm/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jakub/programming/duck/dependencies/glfw-3.1.2/deps/getopt.c > CMakeFiles/clipboard.dir/__/deps/getopt.c.i

dependencies/glm/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clipboard.dir/__/deps/getopt.c.s"
	cd /home/jakub/programming/duck/dependencies/glm/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jakub/programming/duck/dependencies/glfw-3.1.2/deps/getopt.c -o CMakeFiles/clipboard.dir/__/deps/getopt.c.s

dependencies/glm/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.o.requires:

.PHONY : dependencies/glm/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.o.requires

dependencies/glm/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.o.provides: dependencies/glm/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.o.requires
	$(MAKE) -f dependencies/glm/tests/CMakeFiles/clipboard.dir/build.make dependencies/glm/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.o.provides.build
.PHONY : dependencies/glm/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.o.provides

dependencies/glm/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.o.provides.build: dependencies/glm/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.o


# Object files for target clipboard
clipboard_OBJECTS = \
"CMakeFiles/clipboard.dir/clipboard.c.o" \
"CMakeFiles/clipboard.dir/__/deps/getopt.c.o"

# External object files for target clipboard
clipboard_EXTERNAL_OBJECTS =

dependencies/glm/tests/clipboard: dependencies/glm/tests/CMakeFiles/clipboard.dir/clipboard.c.o
dependencies/glm/tests/clipboard: dependencies/glm/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.o
dependencies/glm/tests/clipboard: dependencies/glm/tests/CMakeFiles/clipboard.dir/build.make
dependencies/glm/tests/clipboard: dependencies/glm/src/libglfw3.a
dependencies/glm/tests/clipboard: /usr/lib/x86_64-linux-gnu/librt.so
dependencies/glm/tests/clipboard: /usr/lib/x86_64-linux-gnu/libm.so
dependencies/glm/tests/clipboard: /usr/lib/x86_64-linux-gnu/libX11.so
dependencies/glm/tests/clipboard: /usr/lib/x86_64-linux-gnu/libXrandr.so
dependencies/glm/tests/clipboard: /usr/lib/x86_64-linux-gnu/libXinerama.so
dependencies/glm/tests/clipboard: /usr/lib/x86_64-linux-gnu/libXi.so
dependencies/glm/tests/clipboard: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
dependencies/glm/tests/clipboard: /usr/lib/x86_64-linux-gnu/libXcursor.so
dependencies/glm/tests/clipboard: /usr/lib/x86_64-linux-gnu/libGL.so
dependencies/glm/tests/clipboard: dependencies/glm/tests/CMakeFiles/clipboard.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jakub/programming/duck/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable clipboard"
	cd /home/jakub/programming/duck/dependencies/glm/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clipboard.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/glm/tests/CMakeFiles/clipboard.dir/build: dependencies/glm/tests/clipboard

.PHONY : dependencies/glm/tests/CMakeFiles/clipboard.dir/build

dependencies/glm/tests/CMakeFiles/clipboard.dir/requires: dependencies/glm/tests/CMakeFiles/clipboard.dir/clipboard.c.o.requires
dependencies/glm/tests/CMakeFiles/clipboard.dir/requires: dependencies/glm/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.o.requires

.PHONY : dependencies/glm/tests/CMakeFiles/clipboard.dir/requires

dependencies/glm/tests/CMakeFiles/clipboard.dir/clean:
	cd /home/jakub/programming/duck/dependencies/glm/tests && $(CMAKE_COMMAND) -P CMakeFiles/clipboard.dir/cmake_clean.cmake
.PHONY : dependencies/glm/tests/CMakeFiles/clipboard.dir/clean

dependencies/glm/tests/CMakeFiles/clipboard.dir/depend:
	cd /home/jakub/programming/duck && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jakub/programming/duck /home/jakub/programming/duck/dependencies/glfw-3.1.2/tests /home/jakub/programming/duck /home/jakub/programming/duck/dependencies/glm/tests /home/jakub/programming/duck/dependencies/glm/tests/CMakeFiles/clipboard.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : dependencies/glm/tests/CMakeFiles/clipboard.dir/depend

