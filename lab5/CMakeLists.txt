cmake_minimum_required(VERSION 3.10)
project(lab3)
set(CUR_PR "lab5")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Подключение библиотек
include_directories(include)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false src/*.cpp)
add_library(${CUR_PR}_lib ${SOURCES})

add_executable(${CUR_PR}_exe src/main.cpp)
target_link_libraries(${CUR_PR}_exe PRIVATE ${CUR_PR}_lib)

# target_include_directories(${CUR_PR}_lib PRIVATE include)

# Добавление тестов
add_executable(${CUR_PR}_tests tests/test_${CUR_PR}.cpp)
target_link_libraries(${CUR_PR}_tests ${CUR_PR}_lib gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME ${CUR_PR}tests COMMAND ${CUR_PR}_tests)
