cmake_minimum_required(VERSION 3.11)

project(cobsm)

add_subdirectory(src)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)

    include(FetchContent)
    FetchContent_Declare(
    ctest
    GIT_REPOSITORY https://github.com/StrathbogieBrewing/ctest.git
    GIT_TAG        79d5f55d37ce292a38873e8b214a8716d9b8c35c
    )
    FetchContent_MakeAvailable(ctest)

    add_subdirectory(tests)
    
    add_executable(test_cobsm src/cobsm.c tests/cobsm_test.c)
    target_include_directories(test_cobsm PUBLIC "${ctest_SOURCE_DIR}" include)

endif()


