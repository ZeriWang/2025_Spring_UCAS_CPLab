cmake_minimum_required(VERSION 3.5)

project(Compiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# 尝试查找LLVM
find_package(LLVM QUIET)

if(LLVM_FOUND)
    message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
    message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
    
    # 添加LLVM头文件路径
    include_directories(${LLVM_INCLUDE_DIRS})
    separate_arguments(LLVM_DEFINITIONS_LIST UNIX_COMMAND "${LLVM_DEFINITIONS}")
    add_definitions(${LLVM_DEFINITIONS_LIST})
    add_definitions(-DLLVM_AVAILABLE)
    
    # 获取LLVM库
    llvm_map_components_to_libnames(llvm_libs support core irreader)
else()
    message(STATUS "LLVM not found, using mock IR generator")
endif()

include_directories(deps/antlr4-runtime/)
include_directories(grammar)
include_directories(src)

FILE(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "grammar/*.cpp")
FILE(GLOB_RECURSE ANTLR_LIB_FILES "deps/antlr4-runtime/*.cpp")

add_definitions(-w -g)
add_library(antlr STATIC ${ANTLR_LIB_FILES})
add_executable(compiler ${SOURCE_FILES})
find_package(Threads REQUIRED)

if(LLVM_FOUND)
    target_link_libraries(compiler antlr Threads::Threads ${llvm_libs})
else()
    target_link_libraries(compiler antlr Threads::Threads)
endif()