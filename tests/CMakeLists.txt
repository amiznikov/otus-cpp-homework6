project(tests)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)

add_executable(test_main CustomContainer_test.cpp)

target_link_libraries(test_main
        gtest
        gtest_main
        "${CMAKE_CURRENT_SOURCE_DIR}/.."
)