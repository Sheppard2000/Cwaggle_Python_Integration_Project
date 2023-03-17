#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <memory>
#include <fstream>
#include <random>
#include <chrono>

#include "CWaggle.h"
#include "ExampleGrids.hpp"
#include "ExampleWorlds.hpp"
#include "../lasso/MyExperiment.hpp"
#include "../lasso/Config.hpp"
#include "../lasso/LassoController.hpp"
#include "../lasso/MyEval.hpp"
#include "../lasso/worlds.hpp"

using namespace std;
using namespace std::chrono;

namespace py = pybind11;

void init() {
    // Not needed here, but maybe there is some setup to be done upon import.
}

void runSimulation() {
    string configFile = "lasso_config.txt";
    Config config;
    config.load(configFile);

    double avgEval = 0;
    for (int i = 0; i < config.numTrials; i++) {
        cerr << "Trial: " << i << "\n";

        // We use i + 1 for the RNG seed because seeds of 0 and 1 seem to generate the
        // same result.
        MyExperiment exp(config, i, i + 1);
        exp.run();
        if (exp.wasAborted())
            cerr << "Trial aborted." << "\n";
        else
            avgEval += exp.getEvaluation();
    }

    cout << "\t" << avgEval / config.numTrials << "\n";
}

PYBIND11_MODULE(cwaggle_bridge, m) {
    init();

    m.doc() = "Allows elements of CWaggle to be called from Python.";

    m.def("runSimulation", &runSimulation);
    m.def("makeSquareWorld", &ExampleWorlds::GetGetSquareWorld);
    

    py::class_<Vec2>(m, "Vec2")
        .def(py::init<>())
        .def(py::init<double, double>())
        .def_readwrite("x", &Vec2::x)
        .def_readwrite("y", &Vec2::y);

    py::class_<Entity>(m, "Entity", py::dynamic_attr())
    .def(py::init<>())
    .def("id", &Entity::id)
    .def("isActive", &Entity::isActive)
    .def("setActive", &Entity::setActive)
    .def("tag", &Entity::tag);

    py::class_<CTransform>(m, "CTransform")
        .def(py::init<>())
        .def(py::init<Vec2>())
        .def_readwrite("p", &CTransform::p)
        .def_readwrite("v", &CTransform::v)
        .def_readwrite("a", &CTransform::a)
        .def_readwrite("moved", &CTransform::moved);

    py::class_<CController>(m, "CController")
        .def(py::init<>())
        .def(py::init<std::shared_ptr<EntityController>>());

    py::class_<EntityController>(m, "EntityController")
        .def(py::init<>())
        .def("getAction", &EntityController::getAction)
        .def("getLastAction", &EntityController::getLastAction);
}
