# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /mnt/d/github/TCP-IP-

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/github/TCP-IP-/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TCP_IP_.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TCP_IP_.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TCP_IP_.dir/flags.make

CMakeFiles/TCP_IP_.dir/57.chat_clnt.c.o: CMakeFiles/TCP_IP_.dir/flags.make
CMakeFiles/TCP_IP_.dir/57.chat_clnt.c.o: ../57.chat_clnt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/github/TCP-IP-/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TCP_IP_.dir/57.chat_clnt.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TCP_IP_.dir/57.chat_clnt.c.o   -c /mnt/d/github/TCP-IP-/57.chat_clnt.c

CMakeFiles/TCP_IP_.dir/57.chat_clnt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TCP_IP_.dir/57.chat_clnt.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/github/TCP-IP-/57.chat_clnt.c > CMakeFiles/TCP_IP_.dir/57.chat_clnt.c.i

CMakeFiles/TCP_IP_.dir/57.chat_clnt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TCP_IP_.dir/57.chat_clnt.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/github/TCP-IP-/57.chat_clnt.c -o CMakeFiles/TCP_IP_.dir/57.chat_clnt.c.s

CMakeFiles/TCP_IP_.dir/58.webserv.c.o: CMakeFiles/TCP_IP_.dir/flags.make
CMakeFiles/TCP_IP_.dir/58.webserv.c.o: ../58.webserv.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/github/TCP-IP-/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/TCP_IP_.dir/58.webserv.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TCP_IP_.dir/58.webserv.c.o   -c /mnt/d/github/TCP-IP-/58.webserv.c

CMakeFiles/TCP_IP_.dir/58.webserv.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TCP_IP_.dir/58.webserv.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/github/TCP-IP-/58.webserv.c > CMakeFiles/TCP_IP_.dir/58.webserv.c.i

CMakeFiles/TCP_IP_.dir/58.webserv.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TCP_IP_.dir/58.webserv.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/github/TCP-IP-/58.webserv.c -o CMakeFiles/TCP_IP_.dir/58.webserv.c.s

# Object files for target TCP_IP_
TCP_IP__OBJECTS = \
"CMakeFiles/TCP_IP_.dir/57.chat_clnt.c.o" \
"CMakeFiles/TCP_IP_.dir/58.webserv.c.o"

# External object files for target TCP_IP_
TCP_IP__EXTERNAL_OBJECTS =

TCP_IP_: CMakeFiles/TCP_IP_.dir/57.chat_clnt.c.o
TCP_IP_: CMakeFiles/TCP_IP_.dir/58.webserv.c.o
TCP_IP_: CMakeFiles/TCP_IP_.dir/build.make
TCP_IP_: CMakeFiles/TCP_IP_.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/github/TCP-IP-/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable TCP_IP_"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TCP_IP_.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TCP_IP_.dir/build: TCP_IP_

.PHONY : CMakeFiles/TCP_IP_.dir/build

CMakeFiles/TCP_IP_.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TCP_IP_.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TCP_IP_.dir/clean

CMakeFiles/TCP_IP_.dir/depend:
	cd /mnt/d/github/TCP-IP-/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/github/TCP-IP- /mnt/d/github/TCP-IP- /mnt/d/github/TCP-IP-/cmake-build-debug /mnt/d/github/TCP-IP-/cmake-build-debug /mnt/d/github/TCP-IP-/cmake-build-debug/CMakeFiles/TCP_IP_.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TCP_IP_.dir/depend

