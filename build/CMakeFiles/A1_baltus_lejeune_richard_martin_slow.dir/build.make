# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /net/cremi/slejeune/projetfinal/Projet2048

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /net/cremi/slejeune/projetfinal/Projet2048/build

# Include any dependencies generated for this target.
include CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/flags.make

CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.o: CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/flags.make
CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.o: ../grid.c
	$(CMAKE_COMMAND) -E cmake_progress_report /net/cremi/slejeune/projetfinal/Projet2048/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.o   -c /net/cremi/slejeune/projetfinal/Projet2048/grid.c

CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /net/cremi/slejeune/projetfinal/Projet2048/grid.c > CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.i

CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /net/cremi/slejeune/projetfinal/Projet2048/grid.c -o CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.s

CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.o.requires:
.PHONY : CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.o.requires

CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.o.provides: CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.o.requires
	$(MAKE) -f CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/build.make CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.o.provides.build
.PHONY : CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.o.provides

CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.o.provides.build: CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.o

CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.o: CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/flags.make
CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.o: ../strategy.c
	$(CMAKE_COMMAND) -E cmake_progress_report /net/cremi/slejeune/projetfinal/Projet2048/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.o   -c /net/cremi/slejeune/projetfinal/Projet2048/strategy.c

CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /net/cremi/slejeune/projetfinal/Projet2048/strategy.c > CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.i

CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /net/cremi/slejeune/projetfinal/Projet2048/strategy.c -o CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.s

CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.o.requires:
.PHONY : CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.o.requires

CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.o.provides: CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.o.requires
	$(MAKE) -f CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/build.make CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.o.provides.build
.PHONY : CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.o.provides

CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.o.provides.build: CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.o

# Object files for target A1_baltus_lejeune_richard_martin_slow
A1_baltus_lejeune_richard_martin_slow_OBJECTS = \
"CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.o" \
"CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.o"

# External object files for target A1_baltus_lejeune_richard_martin_slow
A1_baltus_lejeune_richard_martin_slow_EXTERNAL_OBJECTS =

libA1_baltus_lejeune_richard_martin_slow.so: CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.o
libA1_baltus_lejeune_richard_martin_slow.so: CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.o
libA1_baltus_lejeune_richard_martin_slow.so: CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/build.make
libA1_baltus_lejeune_richard_martin_slow.so: CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libA1_baltus_lejeune_richard_martin_slow.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/build: libA1_baltus_lejeune_richard_martin_slow.so
.PHONY : CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/build

CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/requires: CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/grid.c.o.requires
CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/requires: CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/strategy.c.o.requires
.PHONY : CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/requires

CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/cmake_clean.cmake
.PHONY : CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/clean

CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/depend:
	cd /net/cremi/slejeune/projetfinal/Projet2048/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /net/cremi/slejeune/projetfinal/Projet2048 /net/cremi/slejeune/projetfinal/Projet2048 /net/cremi/slejeune/projetfinal/Projet2048/build /net/cremi/slejeune/projetfinal/Projet2048/build /net/cremi/slejeune/projetfinal/Projet2048/build/CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/A1_baltus_lejeune_richard_martin_slow.dir/depend

