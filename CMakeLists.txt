cmake_minimum_required(VERSION 3.27)

project(paley_l3)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 20)

set(IPATHS -I$ENV{HOME}/dev-tools/mosek/10.1/tools/platform/osxaarch64/h)
set(LPATHS -L$ENV{HOME}/dev-tools/mosek/10.1/tools/platform/osxaarch64/bin)

add_custom_target(fusion
        COMMAND make install -C $ENV{HOME}/dev-tools/mosek/10.1/tools/platform/osxaarch64/src/fusion_cxx
)

add_executable(exec main.cpp)

target_compile_options(exec PRIVATE -Wl,-headerpad_max_install_names -stdlib=libc++ -g ${IPATHS})
target_link_options(exec PRIVATE ${LPATHS})
target_link_libraries(exec PRIVATE fusion64 mosek64)

add_dependencies(exec fusion)

add_custom_command(TARGET exec POST_BUILD
        COMMAND install_name_tool -change libfusion64.10.1.dylib $ENV{HOME}/dev-tools/mosek/10.1/tools/platform/osxaarch64/bin/libfusion64.10.1.dylib exec || rm -f exec
        COMMAND install_name_tool -change libmosek64.10.1.dylib $ENV{HOME}/dev-tools/mosek/10.1/tools/platform/osxaarch64/bin/libmosek64.10.1.dylib exec || rm -f exec
)
