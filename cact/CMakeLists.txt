cmake_minimum_required(VERSION 3.15)

project(Compiler LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For macOS, ensure we use the system compiler
if(APPLE)
    set(CMAKE_CXX_COMPILER clang++)
endif()

include_directories(deps/antlr4-runtime)
include_directories(grammar)
include_directories(src)

# Comment out link_directories and link_libraries since we're using source files
# link_directories("dependencies/antlr4-runtime/lib")
# link_libraries(antlr4-runtime)

FILE(GLOB_RECURSE SOURCE_FILES 
    "src/*.cpp" 
    "grammar/*.cpp" 
    "deps/antlr4-runtime/*.cpp"
)

# Add debug symbols and suppress warnings for macOS
add_definitions(-g)
if(APPLE)
    add_definitions(-Wno-everything)
else()
    add_definitions(-w)
endif()

add_executable(compiler ${SOURCE_FILES})
