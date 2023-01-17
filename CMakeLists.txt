cmake_minimum_required(VERSION 3.11)

include(FetchContent)
FetchContent_Declare(
  ctest
  GIT_REPOSITORY https://github.com/StrathbogieBrewing/ctest.git
  GIT_TAG        79d5f55d37ce292a38873e8b214a8716d9b8c35c
)
FetchContent_MakeAvailable(ctest)

project(cobsm)

add_executable(cobsm_test cobsm.c test/cobsm_test.c)

target_include_directories(cobsm_test PUBLIC "${ctest_SOURCE_DIR}")
