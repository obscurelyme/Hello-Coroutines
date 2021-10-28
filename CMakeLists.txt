cmake_minimum_required(VERSION 3.0.0)

set(VCPKG_MANIFEST_MODE ON)

project(hello-co VERSION 0.1.0)

find_package(Boost REQUIRED COMPONENTS context)

add_executable(hello-co main.cpp)
target_link_libraries(hello-co PRIVATE ${Boost_LIBRARIES})
target_include_directories(hello-co PUBLIC ${Boost_INCLUDE_DIRS})