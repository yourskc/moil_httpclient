cmake_minimum_required(VERSION 3.0)
include(FindPkgConfig)
pkg_check_modules(CURLPP REQUIRED curlpp)

set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11
find_package(OpenCV REQUIRED)
include_directories( include /usr/local/include/opencv4 )
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(moilclient moilclient.cpp)
target_link_libraries(moilclient ${CURLPP_LDFLAGS})



