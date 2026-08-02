cmake_minimum_required(VERSION 3.14)
project(edge_camera_pipeline)

# C++20, строго, без GNU-расширений — из чек-листа плана
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warnings как ошибки — ловим проблемы на этапе компиляции (вспомни -Wall из Дня 2)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Нужно clangd'у, чтобы понимать твои инклюды в многофайловом проекте
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(edge_camera_pipeline src/main.cpp)

# --- Тесты через FetchContent ---
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(unit_tests tests/test_main.cpp)
target_link_libraries(unit_tests PRIVATE GTest::gtest_main)
