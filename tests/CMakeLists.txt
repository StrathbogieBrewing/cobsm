cmake_minimum_required(VERSION 3.18)

include(FetchContent)

FetchContent_Declare(
  ctest
  GIT_REPOSITORY git@github.com:StrathbogieBrewing/ctest.git
  GIT_TAG        v1.0.0
)

FetchContent_MakeAvailable(ctest)

project(cobsm_test)

add_compile_options(-DCTEST_ENABLED)

add_executable(cobsm_test ../src/cobsm.c cobsm_test.c)
target_include_directories(cobsm_test PUBLIC ../include/cobsm ${ctest_SOURCE_DIR}/include/ctest)



