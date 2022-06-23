cmake_minimum_required (VERSION 3.22)
project(cmake_example)

ADD_SUBDIRECTORY(proto)

include_directories(${CMAKE_BINARY_DIR}/proto)

include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v2.9.2
)
FetchContent_MakeAvailable(pybind11)

pybind11_add_module(cmake_example src/main.cpp)

target_link_libraries(
    cmake_example
    PRIVATE proto_test

)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(cmake_example
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})

install(TARGETS cmake_example DESTINATION .)