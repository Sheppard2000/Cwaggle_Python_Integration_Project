#include <pybind11/pybind11.h>
#include <algorithm>
#include <iostream>
#include "outside.hpp"

namespace py = pybind11;

int add(int x, int y) 
{
    return x + y;
}

int sub(int x, int y)
{
    return x - y;
}

int sub_and_add(int x, int y, int z)
{
    return add(x, y) + sub (x, z);
}

std::string reverse(std::string str)
{
    std::reverse(str.begin(), str.end());

    return str;
}

void test_suite()
{
    int x = 7; int y = 5;
    std::string str = "I am a triceratops";

    std::cout << "x is 7" << std::endl;
    std::cout << "y is 5" << std::endl;
    std::cout << "x + y is" << add(x, y) << std::endl;
    std::cout << "x - y is" << sub(x, y) << std::endl;
    std::cout << str << std::endl;
    std::cout << reverse(str) << std::endl;
}



PYBIND11_MODULE(example, m) 
{
    m.doc() = "pybind11 example plugin";

    m.def("add", &add, "A function that takes in two numbers and adds them");
    m.def("sub", &sub, "A function that takes in two numbers and subtracts the second number from the first number");
    m.def("sna", &sub_and_add, "A function that takes in three numbers. It adds together the first and second numbers, subtracts the first and third numbers, then adds the two products together");
    m.def("reverse", &reverse, "A function to reverse a string");
    m.def("test_suite", &test_suite, "a testing suite for learning pybind11");
    m.def("printMessage", &printMessage, "prints a simple message");
    m.def("newTracker", &newTracker, "establishes a new tracker");
    m.def("getID", &getID, "get the trackers ID");
    m.def("getPosX", &getPosX, "get the trackers x position");
    m.def("getPosY", &getPosY, "get the trackers y position");
    m.def("updatePos", &updatePos, "update the trackers position");

    py::class_<pet>(m, "pet")
        .def(py::init<double, double>())
        .def("getStats", &pet::getStats);

}