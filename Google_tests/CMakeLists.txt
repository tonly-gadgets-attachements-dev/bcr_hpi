project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(/include)

add_executable(Google_Tests_run hpi_tests.cpp bcr_cypd3177_mock_test.cpp bcr_mock.h bcr_mock.c)

target_link_libraries(Google_Tests_run gtest gtest_main)