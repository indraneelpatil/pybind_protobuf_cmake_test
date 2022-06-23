#include <pybind11/pybind11.h>
#include "integer.pb.h"
#include "pybind11_protobuf/native_proto_caster.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) {
    return i + j;
}

int add_proto(MyInteger i, MyInteger j) {
    return i.num() + j.num();
}

MyInteger return_proto(void) {

    MyInteger test;
    return test;
}

namespace py = pybind11;

PYBIND11_MODULE(cmake_example, m) {

    pybind11_protobuf::ImportNativeProtoCasters();
    m.def("add", &add, R"pbdoc(
        Add two numbers
        Some other explanation about the add function.
    )pbdoc");

    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers
        Some other explanation about the subtract function.
    )pbdoc");

    m.def("return_proto", &return_proto);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
