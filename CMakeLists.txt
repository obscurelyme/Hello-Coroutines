cmake_minimum_required(VERSION 3.0.0)

set(VCPKG_MANIFEST_MODE ON)

set(CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 20)

project(hello-co VERSION 0.1.0)

if (APPLE)
  set(VCPKG_LOCAL_INSTALLED "${PROJECT_BINARY_DIR}/vcpkg_installed/x64-osx")
  message("VCPKG Installed: " ${VCPKG_LOCAL_INSTALLED})
endif()

find_package(Boost REQUIRED COMPONENTS context)

add_library(co INTERFACE)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE ${Boost_LIBRARIES})
target_include_directories(main PUBLIC ${Boost_INCLUDE_DIRS})
# target_include_directories(hello-co PUBLIC ${VCPKG_LOCAL_INSTALLED}/include)
add_executable(tutorial tutorial.cpp)
target_link_libraries(tutorial PRIVATE ${Boost_LIBRARIES})
target_include_directories(tutorial PUBLIC ${Boost_INCLUDE_DIRS})


add_executable(hello-co co-test.cpp)
target_include_directories(co INTERFACE ${VCPKG_LOCAL_INSTALLED}/include)
target_link_libraries(co INTERFACE ${VCPKG_LOCAL_INSTALLED}/debug/lib/libco.a)
target_link_libraries(hello-co PRIVATE co)

add_executable(coro co.cpp)
