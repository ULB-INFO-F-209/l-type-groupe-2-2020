# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /snap/clion/137/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/137/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/l-type-groupe-2-2020/jeu

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/l-type-groupe-2-2020/jeu/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/jeu.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jeu.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jeu.dir/flags.make

CMakeFiles/jeu.dir/main.cpp.o: CMakeFiles/jeu.dir/flags.make
CMakeFiles/jeu.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/l-type-groupe-2-2020/jeu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jeu.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jeu.dir/main.cpp.o -c /home/ubuntu/l-type-groupe-2-2020/jeu/main.cpp

CMakeFiles/jeu.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jeu.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/l-type-groupe-2-2020/jeu/main.cpp > CMakeFiles/jeu.dir/main.cpp.i

CMakeFiles/jeu.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jeu.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/l-type-groupe-2-2020/jeu/main.cpp -o CMakeFiles/jeu.dir/main.cpp.s

# Object files for target jeu
jeu_OBJECTS = \
"CMakeFiles/jeu.dir/main.cpp.o"

# External object files for target jeu
jeu_EXTERNAL_OBJECTS =

jeu: CMakeFiles/jeu.dir/main.cpp.o
jeu: CMakeFiles/jeu.dir/build.make
jeu: CMakeFiles/jeu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/l-type-groupe-2-2020/jeu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable jeu"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jeu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jeu.dir/build: jeu

.PHONY : CMakeFiles/jeu.dir/build

CMakeFiles/jeu.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jeu.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jeu.dir/clean

CMakeFiles/jeu.dir/depend:
	cd /home/ubuntu/l-type-groupe-2-2020/jeu/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/l-type-groupe-2-2020/jeu /home/ubuntu/l-type-groupe-2-2020/jeu /home/ubuntu/l-type-groupe-2-2020/jeu/cmake-build-debug /home/ubuntu/l-type-groupe-2-2020/jeu/cmake-build-debug /home/ubuntu/l-type-groupe-2-2020/jeu/cmake-build-debug/CMakeFiles/jeu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jeu.dir/depend
