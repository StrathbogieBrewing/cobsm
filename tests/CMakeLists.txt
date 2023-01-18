cmake_minimum_required(VERSION 3.11)

project(cobsm)

include(FetchContent)
FetchContent_Declare(
    ctest
    GIT_REPOSITORY https://github.com/StrathbogieBrewing/ctest.git
    GIT_TAG        79d5f55d37ce292a38873e8b214a8716d9b8c35c
)
FetchContent_MakeAvailable(ctest)
add_executable(test_cobsm ../src/cobsm.c cobsm_test.c)
target_include_directories(test_cobsm PUBLIC "${ctest_SOURCE_DIR}" ../include)



