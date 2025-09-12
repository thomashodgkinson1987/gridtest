# Specifies the minimum version of CMake required.
cmake_minimum_required(VERSION 3.15)

# Define the project name, version, and language.
project(GridTest VERSION 1.0 LANGUAGES C)

# Set the C standard.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# --- Submodules ---
# Add our custom libraries. Their CMakeLists.txt files will define targets
# named 'array_macros' and 'queue_macros'.
add_subdirectory(vendor/array_macros)
add_subdirectory(vendor/queue-macros)

# Add the Raylib library. Its CMakeLists.txt will define a target named 'raylib'.
add_subdirectory(lib/raylib)

# --- Project Sources ---
# List all of our project's source files.
set(SOURCES
    src/main.c
    src/actor.c
    src/actor_array.c
    src/actor_hash_map.c
    src/command.c
    src/command_queue.c
    src/command_result.c
    src/command_system.c
    src/component.c
    src/component_array.c
    src/game.c
    src/input_event_queue.c
    src/input_system.c
    src/log.c
    src/renderer.c
    src/world.c
)

# --- Executable Definition ---
# Define the executable target and provide its source files.
add_executable(gridtest ${SOURCES})

# --- Linking ---
# Link our 'gridtest' executable against all required library targets.
# This single command handles everything: it finds the libraries, adds the
# correct include directories, and links them in the proper order.
target_link_libraries(gridtest
    PRIVATE
    raylib
    array_macros
    queue_macros
    m
    pthread
)

# --- Include Directories ---
# Explicitly add our project's 'include' directory to the target.
# This is the modern way to manage include paths.
target_include_directories(gridtest PRIVATE include)

# --- IDE Integration ---
# Set the working directory for when the debugger launches the executable.
# This ensures that relative paths (like "res/font.png") work correctly.
set_target_properties(gridtest PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# --- Custom Run Target ---
# Creates a `make run` command that builds and then executes the program
# from the project root directory. This ensures assets in 'res' are found.
add_custom_target(run
    COMMAND $<TARGET_FILE:gridtest>
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    DEPENDS gridtest
    COMMENT "Running gridtest from ${CMAKE_SOURCE_DIR}"
)
