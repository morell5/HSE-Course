# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /snap/cmake/715/bin/cmake

# The command to remove a file.
RM = /snap/cmake/715/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download

# Utility rule file for googletest.

# Include the progress variables for this target.
include CMakeFiles/googletest.dir/progress.make

CMakeFiles/googletest: CMakeFiles/googletest-complete


CMakeFiles/googletest-complete: googletest-prefix/src/googletest-stamp/googletest-install
CMakeFiles/googletest-complete: googletest-prefix/src/googletest-stamp/googletest-mkdir
CMakeFiles/googletest-complete: googletest-prefix/src/googletest-stamp/googletest-download
CMakeFiles/googletest-complete: googletest-prefix/src/googletest-stamp/googletest-update
CMakeFiles/googletest-complete: googletest-prefix/src/googletest-stamp/googletest-patch
CMakeFiles/googletest-complete: googletest-prefix/src/googletest-stamp/googletest-configure
CMakeFiles/googletest-complete: googletest-prefix/src/googletest-stamp/googletest-build
CMakeFiles/googletest-complete: googletest-prefix/src/googletest-stamp/googletest-install
CMakeFiles/googletest-complete: googletest-prefix/src/googletest-stamp/googletest-test
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'googletest'"
	/snap/cmake/715/bin/cmake -E make_directory /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/CMakeFiles
	/snap/cmake/715/bin/cmake -E touch /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/CMakeFiles/googletest-complete
	/snap/cmake/715/bin/cmake -E touch /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/googletest-prefix/src/googletest-stamp/googletest-done

googletest-prefix/src/googletest-stamp/googletest-install: googletest-prefix/src/googletest-stamp/googletest-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No install step for 'googletest'"
	cd /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-build && /snap/cmake/715/bin/cmake -E echo_append
	cd /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-build && /snap/cmake/715/bin/cmake -E touch /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/googletest-prefix/src/googletest-stamp/googletest-install

googletest-prefix/src/googletest-stamp/googletest-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'googletest'"
	/snap/cmake/715/bin/cmake -E make_directory /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-src
	/snap/cmake/715/bin/cmake -E make_directory /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-build
	/snap/cmake/715/bin/cmake -E make_directory /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/googletest-prefix
	/snap/cmake/715/bin/cmake -E make_directory /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/googletest-prefix/tmp
	/snap/cmake/715/bin/cmake -E make_directory /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/googletest-prefix/src/googletest-stamp
	/snap/cmake/715/bin/cmake -E make_directory /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/googletest-prefix/src
	/snap/cmake/715/bin/cmake -E make_directory /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/googletest-prefix/src/googletest-stamp
	/snap/cmake/715/bin/cmake -E touch /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/googletest-prefix/src/googletest-stamp/googletest-mkdir

googletest-prefix/src/googletest-stamp/googletest-download: googletest-prefix/src/googletest-stamp/googletest-gitinfo.txt
googletest-prefix/src/googletest-stamp/googletest-download: googletest-prefix/src/googletest-stamp/googletest-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'googletest'"
	cd /home/dikson/HSE-Course/module-1/homework/Geometry/build && /snap/cmake/715/bin/cmake -P /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/googletest-prefix/tmp/googletest-gitclone.cmake
	cd /home/dikson/HSE-Course/module-1/homework/Geometry/build && /snap/cmake/715/bin/cmake -E touch /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/googletest-prefix/src/googletest-stamp/googletest-download

googletest-prefix/src/googletest-stamp/googletest-update: googletest-prefix/src/googletest-stamp/googletest-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Performing update step for 'googletest'"
	cd /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-src && /snap/cmake/715/bin/cmake -P /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/googletest-prefix/tmp/googletest-gitupdate.cmake

googletest-prefix/src/googletest-stamp/googletest-patch: googletest-prefix/src/googletest-stamp/googletest-update
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "No patch step for 'googletest'"
	/snap/cmake/715/bin/cmake -E echo_append
	/snap/cmake/715/bin/cmake -E touch /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/googletest-prefix/src/googletest-stamp/googletest-patch

googletest-prefix/src/googletest-stamp/googletest-configure: googletest-prefix/tmp/googletest-cfgcmd.txt
googletest-prefix/src/googletest-stamp/googletest-configure: googletest-prefix/src/googletest-stamp/googletest-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No configure step for 'googletest'"
	cd /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-build && /snap/cmake/715/bin/cmake -E echo_append
	cd /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-build && /snap/cmake/715/bin/cmake -E touch /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/googletest-prefix/src/googletest-stamp/googletest-configure

googletest-prefix/src/googletest-stamp/googletest-build: googletest-prefix/src/googletest-stamp/googletest-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No build step for 'googletest'"
	cd /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-build && /snap/cmake/715/bin/cmake -E echo_append
	cd /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-build && /snap/cmake/715/bin/cmake -E touch /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/googletest-prefix/src/googletest-stamp/googletest-build

googletest-prefix/src/googletest-stamp/googletest-test: googletest-prefix/src/googletest-stamp/googletest-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "No test step for 'googletest'"
	cd /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-build && /snap/cmake/715/bin/cmake -E echo_append
	cd /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-build && /snap/cmake/715/bin/cmake -E touch /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/googletest-prefix/src/googletest-stamp/googletest-test

googletest: CMakeFiles/googletest
googletest: CMakeFiles/googletest-complete
googletest: googletest-prefix/src/googletest-stamp/googletest-build
googletest: googletest-prefix/src/googletest-stamp/googletest-configure
googletest: googletest-prefix/src/googletest-stamp/googletest-download
googletest: googletest-prefix/src/googletest-stamp/googletest-install
googletest: googletest-prefix/src/googletest-stamp/googletest-mkdir
googletest: googletest-prefix/src/googletest-stamp/googletest-patch
googletest: googletest-prefix/src/googletest-stamp/googletest-test
googletest: googletest-prefix/src/googletest-stamp/googletest-update
googletest: CMakeFiles/googletest.dir/build.make

.PHONY : googletest

# Rule to build all files generated by this target.
CMakeFiles/googletest.dir/build: googletest

.PHONY : CMakeFiles/googletest.dir/build

CMakeFiles/googletest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/googletest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/googletest.dir/clean

CMakeFiles/googletest.dir/depend:
	cd /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download /home/dikson/HSE-Course/module-1/homework/Geometry/build/googletest-download/CMakeFiles/googletest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/googletest.dir/depend

