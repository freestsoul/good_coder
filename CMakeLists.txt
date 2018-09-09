cmake_minimum_required(VERSION 3.12)
#add_definitions(-std=c++11)
set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(TARGET_BIN parser)
set(DIR_SRC main.cpp)
#aux_source_directory(. DIR_SRC)

add_executable(${TARGET_BIN} ${DIR_SRC})

target_link_libraries(${TARGET_BIN}
  ${Boost_LIBRARIES}
  #${Boost_FILESYSTEM_LIBRARY}
  #${Boost_SYSTEM_LIBRARY}
  #${Boost_REGEX_LIBRARY}
  )
