# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chloe/liquidfun/Box2D

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chloe/liquidfun/Box2D

# Include any dependencies generated for this target.
include googletest/CMakeFiles/gtest.dir/depend.make

# Include the progress variables for this target.
include googletest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include googletest/CMakeFiles/gtest.dir/flags.make

googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: googletest/CMakeFiles/gtest.dir/flags.make
googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: /home/chloe/googletest/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chloe/liquidfun/Box2D/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o"
	cd /home/chloe/liquidfun/Box2D/googletest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest.dir/src/gtest-all.cc.o -c /home/chloe/googletest/src/gtest-all.cc

googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.cc.i"
	cd /home/chloe/liquidfun/Box2D/googletest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chloe/googletest/src/gtest-all.cc > CMakeFiles/gtest.dir/src/gtest-all.cc.i

googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.cc.s"
	cd /home/chloe/liquidfun/Box2D/googletest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chloe/googletest/src/gtest-all.cc -o CMakeFiles/gtest.dir/src/gtest-all.cc.s

googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires:

.PHONY : googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires

googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides: googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires
	$(MAKE) -f googletest/CMakeFiles/gtest.dir/build.make googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides.build
.PHONY : googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides

googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides.build: googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o


# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.cc.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

googletest/Release/libgtest.a: googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
googletest/Release/libgtest.a: googletest/CMakeFiles/gtest.dir/build.make
googletest/Release/libgtest.a: googletest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chloe/liquidfun/Box2D/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library Release/libgtest.a"
	cd /home/chloe/liquidfun/Box2D/googletest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean_target.cmake
	cd /home/chloe/liquidfun/Box2D/googletest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
googletest/CMakeFiles/gtest.dir/build: googletest/Release/libgtest.a

.PHONY : googletest/CMakeFiles/gtest.dir/build

googletest/CMakeFiles/gtest.dir/requires: googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires

.PHONY : googletest/CMakeFiles/gtest.dir/requires

googletest/CMakeFiles/gtest.dir/clean:
	cd /home/chloe/liquidfun/Box2D/googletest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : googletest/CMakeFiles/gtest.dir/clean

googletest/CMakeFiles/gtest.dir/depend:
	cd /home/chloe/liquidfun/Box2D && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chloe/liquidfun/Box2D /home/chloe/googletest /home/chloe/liquidfun/Box2D /home/chloe/liquidfun/Box2D/googletest /home/chloe/liquidfun/Box2D/googletest/CMakeFiles/gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : googletest/CMakeFiles/gtest.dir/depend

