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
CMAKE_SOURCE_DIR = /home/nhanma/Desktop/uart

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nhanma/Desktop/uart/build

# Include any dependencies generated for this target.
include CMakeFiles/uart_frame.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/uart_frame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/uart_frame.dir/flags.make

CMakeFiles/uart_frame.dir/lib/main.cpp.o: CMakeFiles/uart_frame.dir/flags.make
CMakeFiles/uart_frame.dir/lib/main.cpp.o: ../lib/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nhanma/Desktop/uart/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/uart_frame.dir/lib/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uart_frame.dir/lib/main.cpp.o -c /home/nhanma/Desktop/uart/lib/main.cpp

CMakeFiles/uart_frame.dir/lib/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uart_frame.dir/lib/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nhanma/Desktop/uart/lib/main.cpp > CMakeFiles/uart_frame.dir/lib/main.cpp.i

CMakeFiles/uart_frame.dir/lib/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uart_frame.dir/lib/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nhanma/Desktop/uart/lib/main.cpp -o CMakeFiles/uart_frame.dir/lib/main.cpp.s

CMakeFiles/uart_frame.dir/lib/serialport.cpp.o: CMakeFiles/uart_frame.dir/flags.make
CMakeFiles/uart_frame.dir/lib/serialport.cpp.o: ../lib/serialport.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nhanma/Desktop/uart/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/uart_frame.dir/lib/serialport.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uart_frame.dir/lib/serialport.cpp.o -c /home/nhanma/Desktop/uart/lib/serialport.cpp

CMakeFiles/uart_frame.dir/lib/serialport.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uart_frame.dir/lib/serialport.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nhanma/Desktop/uart/lib/serialport.cpp > CMakeFiles/uart_frame.dir/lib/serialport.cpp.i

CMakeFiles/uart_frame.dir/lib/serialport.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uart_frame.dir/lib/serialport.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nhanma/Desktop/uart/lib/serialport.cpp -o CMakeFiles/uart_frame.dir/lib/serialport.cpp.s

CMakeFiles/uart_frame.dir/lib/bts_get_message.cpp.o: CMakeFiles/uart_frame.dir/flags.make
CMakeFiles/uart_frame.dir/lib/bts_get_message.cpp.o: ../lib/bts_get_message.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nhanma/Desktop/uart/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/uart_frame.dir/lib/bts_get_message.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uart_frame.dir/lib/bts_get_message.cpp.o -c /home/nhanma/Desktop/uart/lib/bts_get_message.cpp

CMakeFiles/uart_frame.dir/lib/bts_get_message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uart_frame.dir/lib/bts_get_message.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nhanma/Desktop/uart/lib/bts_get_message.cpp > CMakeFiles/uart_frame.dir/lib/bts_get_message.cpp.i

CMakeFiles/uart_frame.dir/lib/bts_get_message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uart_frame.dir/lib/bts_get_message.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nhanma/Desktop/uart/lib/bts_get_message.cpp -o CMakeFiles/uart_frame.dir/lib/bts_get_message.cpp.s

CMakeFiles/uart_frame.dir/lib/bts_frame_message.cpp.o: CMakeFiles/uart_frame.dir/flags.make
CMakeFiles/uart_frame.dir/lib/bts_frame_message.cpp.o: ../lib/bts_frame_message.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nhanma/Desktop/uart/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/uart_frame.dir/lib/bts_frame_message.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uart_frame.dir/lib/bts_frame_message.cpp.o -c /home/nhanma/Desktop/uart/lib/bts_frame_message.cpp

CMakeFiles/uart_frame.dir/lib/bts_frame_message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uart_frame.dir/lib/bts_frame_message.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nhanma/Desktop/uart/lib/bts_frame_message.cpp > CMakeFiles/uart_frame.dir/lib/bts_frame_message.cpp.i

CMakeFiles/uart_frame.dir/lib/bts_frame_message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uart_frame.dir/lib/bts_frame_message.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nhanma/Desktop/uart/lib/bts_frame_message.cpp -o CMakeFiles/uart_frame.dir/lib/bts_frame_message.cpp.s

# Object files for target uart_frame
uart_frame_OBJECTS = \
"CMakeFiles/uart_frame.dir/lib/main.cpp.o" \
"CMakeFiles/uart_frame.dir/lib/serialport.cpp.o" \
"CMakeFiles/uart_frame.dir/lib/bts_get_message.cpp.o" \
"CMakeFiles/uart_frame.dir/lib/bts_frame_message.cpp.o"

# External object files for target uart_frame
uart_frame_EXTERNAL_OBJECTS =

uart_frame: CMakeFiles/uart_frame.dir/lib/main.cpp.o
uart_frame: CMakeFiles/uart_frame.dir/lib/serialport.cpp.o
uart_frame: CMakeFiles/uart_frame.dir/lib/bts_get_message.cpp.o
uart_frame: CMakeFiles/uart_frame.dir/lib/bts_frame_message.cpp.o
uart_frame: CMakeFiles/uart_frame.dir/build.make
uart_frame: CMakeFiles/uart_frame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nhanma/Desktop/uart/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable uart_frame"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uart_frame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/uart_frame.dir/build: uart_frame

.PHONY : CMakeFiles/uart_frame.dir/build

CMakeFiles/uart_frame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/uart_frame.dir/cmake_clean.cmake
.PHONY : CMakeFiles/uart_frame.dir/clean

CMakeFiles/uart_frame.dir/depend:
	cd /home/nhanma/Desktop/uart/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nhanma/Desktop/uart /home/nhanma/Desktop/uart /home/nhanma/Desktop/uart/build /home/nhanma/Desktop/uart/build /home/nhanma/Desktop/uart/build/CMakeFiles/uart_frame.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/uart_frame.dir/depend

