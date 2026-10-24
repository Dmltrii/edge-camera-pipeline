cmake_minimum_required(VERSION 3.14)
project(edge_camera_pipeline)

# C++20, строго, без GNU-расширений — из чек-листа плана
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Build with ASan and UBSan" OFF)

# Нужно clangd'у, чтобы понимать твои инклюды в многофайловом проекте
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(edge_camera_pipeline src/main.cpp src/frame_stats.cpp)
target_compile_options(edge_camera_pipeline PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_include_directories(edge_camera_pipeline PRIVATE src)

# --- Тесты через FetchContent ---
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(unit_tests
    tests/test_main.cpp
    tests/test_file_descriptor.cpp
    src/frame_stats.cpp
)
target_compile_options(unit_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(unit_tests PRIVATE GTest::gtest_main)
target_include_directories(unit_tests PRIVATE src)   


function(enable_sanitizers target)
  if(ENABLE_SANITIZERS)
    target_compile_options(${target} PRIVATE
      -fsanitize=address,undefined
      -fno-sanitize-recover=all
      -fno-omit-frame-pointer)
    target_link_options(${target} PRIVATE -fsanitize=address,undefined)
  endif()
endfunction()

enable_sanitizers(edge_camera_pipeline)
enable_sanitizers(unit_tests)

include(GoogleTest)
gtest_discover_tests(unit_tests)  