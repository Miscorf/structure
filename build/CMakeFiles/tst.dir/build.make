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
CMAKE_COMMAND = C:/CMake/bin/cmake.exe

# The command to remove a file.
RM = C:/CMake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/Users/USTC/Desktop/structure

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/Users/USTC/Desktop/structure/build

# Include any dependencies generated for this target.
include CMakeFiles/tst.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tst.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tst.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tst.dir/flags.make

CMakeFiles/tst.dir/src/test.cpp.obj: CMakeFiles/tst.dir/flags.make
CMakeFiles/tst.dir/src/test.cpp.obj: CMakeFiles/tst.dir/includes_CXX.rsp
CMakeFiles/tst.dir/src/test.cpp.obj: C:/Users/USTC/Desktop/structure/src/test.cpp
CMakeFiles/tst.dir/src/test.cpp.obj: CMakeFiles/tst.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/Users/USTC/Desktop/structure/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tst.dir/src/test.cpp.obj"
	C:/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tst.dir/src/test.cpp.obj -MF CMakeFiles/tst.dir/src/test.cpp.obj.d -o CMakeFiles/tst.dir/src/test.cpp.obj -c C:/Users/USTC/Desktop/structure/src/test.cpp

CMakeFiles/tst.dir/src/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tst.dir/src/test.cpp.i"
	C:/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/Users/USTC/Desktop/structure/src/test.cpp > CMakeFiles/tst.dir/src/test.cpp.i

CMakeFiles/tst.dir/src/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tst.dir/src/test.cpp.s"
	C:/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/Users/USTC/Desktop/structure/src/test.cpp -o CMakeFiles/tst.dir/src/test.cpp.s

# Object files for target tst
tst_OBJECTS = \
"CMakeFiles/tst.dir/src/test.cpp.obj"

# External object files for target tst
tst_EXTERNAL_OBJECTS =

C:/Users/USTC/Desktop/structure/bin/tst.exe: CMakeFiles/tst.dir/src/test.cpp.obj
C:/Users/USTC/Desktop/structure/bin/tst.exe: CMakeFiles/tst.dir/build.make
C:/Users/USTC/Desktop/structure/bin/tst.exe: C:/Users/USTC/Desktop/structure/bin/uDASAPI.dll
C:/Users/USTC/Desktop/structure/bin/tst.exe: CMakeFiles/tst.dir/linkLibs.rsp
C:/Users/USTC/Desktop/structure/bin/tst.exe: CMakeFiles/tst.dir/objects1
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:/Users/USTC/Desktop/structure/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable C:/Users/USTC/Desktop/structure/bin/tst.exe"
	C:/CMake/bin/cmake.exe -E rm -f CMakeFiles/tst.dir/objects.a
	C:/mingw64/bin/ar.exe qc CMakeFiles/tst.dir/objects.a @CMakeFiles/tst.dir/objects1
	C:/mingw64/bin/g++.exe -g -Wl,--whole-archive CMakeFiles/tst.dir/objects.a -Wl,--no-whole-archive -o C:/Users/USTC/Desktop/structure/bin/tst.exe -Wl,--out-implib,C:/Users/USTC/Desktop/structure/bin/libtst.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/tst.dir/linkLibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/tst.dir/build: C:/Users/USTC/Desktop/structure/bin/tst.exe
.PHONY : CMakeFiles/tst.dir/build

CMakeFiles/tst.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tst.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tst.dir/clean

CMakeFiles/tst.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/USTC/Desktop/structure C:/Users/USTC/Desktop/structure C:/Users/USTC/Desktop/structure/build C:/Users/USTC/Desktop/structure/build C:/Users/USTC/Desktop/structure/build/CMakeFiles/tst.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tst.dir/depend
