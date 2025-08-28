# Specifies the minimum version of CMake required.
cmake_minimum_required(VERSION 3.10)

# Define the project name, version, and language.
project(GridTest VERSION 1.0 LANGUAGES C)

# Set the C standard you want to use (C11 or C17 are good choices).
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# --- Dependency Handling (Raylib) ---
# Since you have raylib pre-compiled, we'll tell CMake where to find its
# header and library files directly.

# Add your 'include' directory to the list of directories to search for headers.
include_directories(include)

# Define a variable for the raylib library path.
set(RAYLIB_LIBRARY ${CMAKE_SOURCE_DIR}/lib/libraylib.so.5.5.0)

# --- Submodules ---
# Add the array_macros library from the vendor directory.
# This makes the 'array_macros' INTERFACE target available.
add_subdirectory(vendor/array_macros)

# --- Project Sources ---
# List all your .c source files in the 'src' directory explicitly.
set(SOURCES
    src/main.c
    src/actor.c
    src/actor_array.c
    src/command.c
    src/command_array.c
    src/command_result.c
    src/command_system.c
    src/components.c
    src/game.c
    src/log.c
    src/renderer.c
    src/world.c
)

# --- Executable Definition ---
# Define the executable target and give it a name.
add_executable(gridtest ${SOURCES})

# --- IDE Integration ---
# Set the working directory for when the debugger launches the executable.
# This ensures that relative paths (like "res/font.png") work correctly.
set_target_properties(gridtest PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# --- RPATH Handling ---
# Embed a runtime search path (RPATH) into the executable. This tells the
# dynamic linker where to find the raylib .so file. Using $ORIGIN makes the
# executable portable even after compilation.
# $ORIGIN resolves to the executable's directory, so ../lib finds the lib folder.
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")

# --- Linking ---
# Link your executable against all required libraries.
target_link_libraries(gridtest
    PRIVATE
    array_macros
    ${RAYLIB_LIBRARY}
    m
    pthread
)

# --- Optional: For Development ---
# If you're using VSCode with the CMake Tools extension, this helps it find headers.
target_include_directories(gridtest PRIVATE ${CMAKE_SOURCE_DIR}/include)

# --- Custom Run Target ---
# Creates a `make run` command that builds and then executes the program
# from the project root directory. This ensures assets in 'res' are found.
add_custom_target(run
    COMMAND $<TARGET_FILE:gridtest>
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    DEPENDS gridtest
    COMMENT "Running gridtest from ${CMAKE_SOURCE_DIR}"
)

