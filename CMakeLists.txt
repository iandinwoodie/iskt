cmake_minimum_required(VERSION 3.0)
project(Iskt)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)

add_library(isktlib SHARED
  include/Client.h
  include/Server.h
  src/Client.cpp
  src/Server.cpp
)
target_include_directories(isktlib
  PUBLIC
    include
)
target_link_libraries(isktlib
  Qt5::Core
  Qt5::Network
)

add_executable(iskt
  src/Main.cpp
)
target_link_libraries(iskt
  isktlib
)
