cmake_minimum_required(VERSION 3.22)

project (NativeWindow)
set (CMAKE_CXX_STANDARD 17)

# ======== Library name ========
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set (COMPILER_TYPE "clang")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set (COMPILER_TYPE "gcc")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set (COMPILER_TYPE "msvc")
else ()
    set (COMPILER_TYPE "unknown")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(ARTIFACT_NAME "native_window_${COMPILER_TYPE}_d")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(ARTIFACT_NAME "native_window_${COMPILER_TYPE}")
endif ()

# ======== Library source files ========
file (GLOB_RECURSE NATIVE_WINDOW_SRC ./src/*.cpp)
file (GLOB_RECURSE IMGUI_SRC
        ./thirdparty/imgui/imgui.cpp
        ./thirdparty/imgui/imgui_draw.cpp
        ./thirdparty/imgui/imgui_tables.cpp
        ./thirdparty/imgui/imgui_widgets.cpp
        ./thirdparty/imgui/backends/imgui_impl_win32.cpp
        ./thirdparty/imgui/backends/imgui_impl_dx11.cpp
        ./thirdparty/imgui/backends/imgui_impl_opengl3.cpp
        ./thirdparty/imgui/backends/imgui_impl_vulkan.cpp
)

# ======== Required packages ========
find_package(Vulkan REQUIRED)

# ======== Library target ========
set                         (TARGET_NAME "native_window")
add_library                 (${TARGET_NAME} STATIC  ${NATIVE_WINDOW_SRC} ${IMGUI_SRC})
target_include_directories  (${TARGET_NAME} PUBLIC  ./include/)
target_include_directories  (${TARGET_NAME} PUBLIC  ./thirdparty/imgui/)
target_include_directories  (${TARGET_NAME} PRIVATE ./thirdparty/glad/)
set_target_properties       (${TARGET_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/artifacts/NativeWindow/lib/")
set_target_properties       (${TARGET_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/artifacts/NativeWindow/lib/")
set_target_properties       (${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/artifacts/NativeWindow/lib/")
set_target_properties       (${TARGET_NAME} PROPERTIES OUTPUT_NAME "${ARTIFACT_NAME}")
target_link_libraries       (${TARGET_NAME} PUBLIC Vulkan::Vulkan)
target_compile_definitions  (${TARGET_NAME} PUBLIC VK_USE_PLATFORM_WIN32_KHR)

# ======== Tests ========
option (ENABLE_NATIVE_WINDOW_TEST OFF)

if (ENABLE_NATIVE_WINDOW_TEST)
    add_executable          (test_create test/TestWindowCreate.cpp)
    target_link_libraries   (test_create PUBLIC ${TARGET_NAME})
    set_target_properties   (test_create PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

    add_executable          (test_msg_recv test/TestMessageReceived.cpp)
    target_link_libraries   (test_msg_recv PUBLIC ${TARGET_NAME})

    add_executable          (test_window_callback test/TestWindowCallback.cpp)
    target_link_libraries   (test_window_callback PUBLIC ${TARGET_NAME})

    add_executable          (test_input_callback test/TestInputCallback.cpp)
    target_link_libraries   (test_input_callback PUBLIC ${TARGET_NAME})

    add_executable          (test_imgui_opengl test/TestImGuiOpenGL.cpp)
    target_link_libraries   (test_imgui_opengl PUBLIC ${TARGET_NAME})
endif ()