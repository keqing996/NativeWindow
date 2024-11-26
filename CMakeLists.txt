cmake_minimum_required(VERSION 3.22)

project (NativeWindow)

set (CMAKE_CXX_STANDARD 17)

file (GLOB_RECURSE NATIVE_WINDOW_SRC ./src/*.cpp)

add_library                 (native_window STATIC ${NATIVE_WINDOW_SRC})
target_include_directories  (native_window PUBLIC ./include/)

option (ENABLE_NATIVE_WINDOW_TEST OFF)

if (ENABLE_NATIVE_WINDOW_TEST)
    add_executable          (test_create test/TestWindowCreate.cpp)
    target_link_libraries   (test_create PUBLIC native_window)
    set_target_properties   (test_create PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

    add_executable          (test_msg_recv test/TestMessageReceived.cpp)
    target_link_libraries   (test_msg_recv PUBLIC native_window)

    add_executable          (test_callback test/TestCallback.cpp)
    target_link_libraries   (test_callback PUBLIC native_window)
endif ()