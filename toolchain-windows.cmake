# toolchain-windows.cmake

# Set the target system name for CMake.
set(CMAKE_SYSTEM_NAME Windows)

# Set the C compiler to the MinGW-w64 cross-compiler.
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)

# Set the CXX (C++) compiler to the MinGW-w64 cross-compiler.
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
