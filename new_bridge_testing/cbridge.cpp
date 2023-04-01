#include <pybind11/pybind11.h>
#include <iostream>

#include "TestCode.hpp"

PYBIND11_MODULE(cbridge, m)
{
    m.doc() = "Testing for pybind11";

    m.def("testFunc", &testFunc);
}