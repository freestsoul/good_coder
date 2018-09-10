cmake_minimum_required(VERSION 3.12)
#add_definitions(-std=c++11)
set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-g -Wall")

set(TARGET_BIN parser)
set(DIR_SRC src/main.cpp)
#aux_source_directory(. DIR_SRC)

add_executable(${TARGET_BIN} ${DIR_SRC})

target_link_libraries(${TARGET_BIN}
  ${Boost_LIBRARIES}
  #${Boost_FILESYSTEM_LIBRARY}
  #${Boost_SYSTEM_LIBRARY}
  #${Boost_REGEX_LIBRARY}
  )

# Options. Turn on with 'cmake -Dmyvarname=ON'
option(test "Build all test." OFF)

################################
# Testing
################################
if (test)
  find_package(GTest)
  #enable_testing()
  #include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
  include_directories(${gtest_INCLUDE_DIRS})

  ##############
  # Unit Tests
  ##############
  add_executable(runParseCommTypeTest test/test_ParseCommType.cpp)
  add_executable(runParseCustomTypeTest test/test_ParseCustomType.cpp)
  add_executable(runCustomTypeExampleTest test/test_CustomType.cpp)
  add_executable(runParserTest test/test_Parser.cpp)

  # Standard linking to gtest stuff.
  # Link test executable against gtest & gtest_main
  target_link_libraries(runParseCommTypeTest gtest gtest_main)
  target_link_libraries(runParseCustomTypeTest gtest gtest_main)
  target_link_libraries(runCustomTypeExampleTest gtest gtest_main)
  target_link_libraries(runParserTest gtest gtest_main)

  # Extra linking for the project.
  #target_link_libraries(runUnitTests ...)

  # This is so you can do 'make test' to see all your tests run, instead of
  # manually running the executable runUnitTests to see those specific tests.
  add_test(NAME that-test-I-made COMMAND runParseCommTypeTest)

  # You can also omit NAME and COMMAND. The second argument could be some other
  # test executable.
  #add_test(that-other-test-I-made runUnitTests)

endif()
