cmake_minimum_required(VERSION 3.27)

project(paley_l3)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Read environment variables from .env.local
file(STRINGS ${CMAKE_SOURCE_DIR}/env/.env.local ENV_VARIABLES)

# Process each line in .env.local to set CMake variables
foreach(ENV_VAR ${ENV_VARIABLES})
    string(REGEX REPLACE "([^=]+)=(.*)" "\\1;\\2" ENV_VAR_PARTS ${ENV_VAR})
    list(GET ENV_VAR_PARTS 0 VAR_NAME)
    list(GET ENV_VAR_PARTS 1 VAR_VALUE)
    set(${VAR_NAME} ${VAR_VALUE})
endforeach()

set(IPATHS -I$ENV{HOME}/${MSKHOME}/mosek/10.1/tools/platform/${PLATFORM}/h)
set(LPATHS -L$ENV{HOME}/${MSKHOME}/mosek/10.1/tools/platform/${PLATFORM}/bin)

add_custom_target(fusion
        COMMAND make install -C $ENV{HOME}/${MSKHOME}/mosek/10.1/tools/platform/${PLATFORM}/src/fusion_cxx
)

add_executable(exec main.cpp)

target_compile_options(exec PRIVATE -Wl,-headerpad_max_install_names -stdlib=libc++ -g ${IPATHS})
target_link_options(exec PRIVATE ${LPATHS})
target_link_libraries(exec PRIVATE fusion64 mosek64)

add_dependencies(exec fusion)

add_custom_command(TARGET exec POST_BUILD
        COMMAND install_name_tool -change libfusion64.10.1.dylib $ENV{HOME}/${MSKHOME}/mosek/10.1/tools/platform/${PLATFORM}/bin/libfusion64.10.1.dylib exec || rm -f exec
        COMMAND install_name_tool -change libmosek64.10.1.dylib $ENV{HOME}/${MSKHOME}/mosek/10.1/tools/platform/${PLATFORM}/bin/libmosek64.10.1.dylib exec || rm -f exec
)
