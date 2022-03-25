project(Google_tests)
add_definitions(-DBUILD_GMOCK)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_executable(Google_Tests_run hpi_tests.cpp bcr_cypd3177_mock_test.cpp bcr_mock.h bcr_mock.c ../bcr_hpi.c ../bcr_hpi.h)

target_link_libraries(Google_Tests_run gtest gtest_main)