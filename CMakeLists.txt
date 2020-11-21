cmake_minimum_required(VERSION 3.17)
project(Translit)

enable_testing()

add_definitions(-std=gnu++17 -U__STRICT_ANSI__)

set(LINKER_FLAGS1 -lcygwin)
set(LINKER_FLAGS2 -lSDL2main)
set(LINKER_FLAGS3 -lSDL2)
set(LINKER_FLAGS4 -mwindows)

add_subdirectory(googletest)

include_directories(src) # необходимо для того, чтобы писать в директиве просто lib.h
include_directories(googletest/googletest/include)

set(SOURCE_FILES src/lib.cpp)

add_executable(main main.cpp ${SOURCE_FILES})
add_executable(tests tests.cpp ${SOURCE_FILES})

target_link_libraries(tests gtest)