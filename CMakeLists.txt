cmake_minimum_required (VERSION 3.22)
project(cmake_example)

ADD_SUBDIRECTORY(proto)

# To compile shared libs for protobuf
option(BUILD_SHARED_LIBS "isso é um teste" ON)

set(ABSL_PROPAGATE_CXX_STD ON)
find_package(Python COMPONENTS Interpreter Development REQUIRED)

include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v2.9.2
)
FetchContent_MakeAvailable(pybind11)

FetchContent_Declare(
  pybind11_protobuf
  GIT_REPOSITORY https://github.com/pybind/pybind11_protobuf.git
  GIT_TAG        main
)

FetchContent_MakeAvailable(pybind11_protobuf)


FetchContent_Declare(
  abseil_cpp
  GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(abseil_cpp)

FetchContent_Declare(
  protobuf
  GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
  GIT_TAG        main
)

FetchContent_MakeAvailable(protobuf)

include_directories(proto)
include_directories(${CMAKE_BINARY_DIR}/proto)
include_directories(${pybind11_protobuf_SOURCE_DIR} ${abseil_cpp_SOURCE_DIR} ${Python_INCLUDE_DIRECTORIES} ${protobuf_SOURCE_DIR} )

pybind11_add_module(cmake_example 
                    src/main.cpp
                    ${pybind11_protobuf_SOURCE_DIR}//pybind11_protobuf/native_proto_caster.cc
                    ${pybind11_protobuf_SOURCE_DIR}//pybind11_protobuf/proto_cast_util.cc
                    ${pybind11_protobuf_SOURCE_DIR}//pybind11_protobuf/proto_utils.cc
                    )

target_link_libraries(
    cmake_example
    PRIVATE proto_test
    PRIVATE protobuf::libprotobuf
    PRIVATE absl::hash 
    PRIVATE absl::flat_hash_map
)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(cmake_example
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})

install(TARGETS cmake_example DESTINATION .)