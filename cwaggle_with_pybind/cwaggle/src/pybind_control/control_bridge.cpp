#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "CWaggle.h"
#include "EntityAction.hpp"

#include <sstream>
#include <iostream>

namespace py = pybind11;

class PybindControl
{
    std::shared_ptr<World> world;
    std::shared_ptr<Simulator> simulator;
    std::shared_ptr<GUI> gui;
    double simulationTimeStep = 1.0;
    double stepsPerRender = 1;
    //bool initialized = false;
    int robotIndex = 0;

public:
    PybindControl()
    {
        world = std::make_shared<World>(800, 800);
        //std::cout << "The Worlds Parameters are height: " << world->height() << " width: " << world->width() << std::endl;

        //add robots to the world
        for(size_t r = 0; r < 1; r++)
        {
            Entity robot = world->addEntity("robot");
            //std::cout << "robot id: " << robot.id() << std::endl;
            Vec2 rPos(rand() % 800, rand() % 800);
            robot.addComponent<CTransform>(rPos);
            robot.addComponent<CCircleBody>(10);
            robot.addComponent<CCircleShape>(10);
            robot.addComponent<CColor>(0, 100, 200, 255);
            robot.addComponent<CRobotType>(0);
            //std::cout << "Add robot sensor array" << std::endl;
            robot.addComponent<CSensorArray>();
            //std::cout << "Add robot sensor" << std::endl;
            robot.getComponent<CSensorArray>().obstacleSensors.push_back(std::make_shared<ObstacleSensor>(robot, "frontOBS", 0, 20, 8));
            robot.getComponent<CSensorArray>().obstacleSensors.push_back(std::make_shared<ObstacleSensor>(robot, "rightOBS", 45, 20, 8));
            robot.getComponent<CSensorArray>().obstacleSensors.push_back(std::make_shared<ObstacleSensor>(robot, "leftOBS", 315, 20, 8));
        }

        //world->update();
        //std::cout << "There are " << world->getEntities("robot").size() << " Robots in the world" << std::endl;

        //add pucks to the world
        for(size_t p = 0; p < 150; p++)
        {
            int rWidth = rand() % 720;
            int rHeight = rand() % 720;
            Vec2 pPos(40 + rWidth, 40 + rHeight);

            Entity puck = world->addEntity("red_puck");
            puck.addComponent<CTransform>(pPos);
            puck.addComponent<CCircleBody>(10);
            puck.addComponent<CCircleShape>(10);
            puck.addComponent<CColor>(200, 44, 44, 255);
        }

        //world->update();
        //std::cout << "There are " << world->getEntities("puck").size() << " Pucks in the world" << std::endl;

        //std::cout << "There are " << world->getEntities().size() << " Entities in the world" << std::endl;

        //make value grid
        ValueGrid grid(800, 800);

        for (size_t x = 0; x < 800; x++)
        {
            for (size_t y = 0; y < 800; y++)
            {
                grid.set(x, y, Vec2(x, y).dist(Vec2(800 / 2.0, 800 / 2.0)));
            }
        }

        grid.normalize();
        grid.invert();

        world->addGrid(grid);
        world->update();

        simulator = std::make_shared<Simulator>(world);

        //set up the GUI
        //GUI gui(simulator, 144);
        //initialized = true;
    }

    int numberOfEntities()
    {
        //std::cout << world->getEntities().size() << std::endl;
        return world->getEntities().size();
    }

    int numberOfRobots()
    {
        return world->getEntities("robot").size();
    }

    double getStepsPerRender()
    {
        return stepsPerRender;
    }

    void simulatorUpdate()
    {
        simulator->update(simulationTimeStep);
    }

    bool isGUI()
    {
        if(gui)
        {
            //std::cout << "yes" << std::endl;
            return true;
        }
        else
        {
            //std::cout << "no" << std::endl;
            return false;
        }
    }

    void makeGUI()
    {
        gui = std::make_shared<GUI>(simulator, 144);
    }

    void updateGUI()
    {
        gui->update();
    }

    void moveForward(Entity &robot)
    {
        EntityAction action;

        const double forwardSpeed = 1.0;
        const double angularSpeed = 0.0;


        action = EntityAction(forwardSpeed, angularSpeed);
        action.doAction(robot, simulationTimeStep);
    }

    void turnRight(Entity &robot)
    {
        EntityAction action;

        const double forwardSpeed = 1.0;
        const double angularSpeed = 0.0009;

        action = EntityAction(forwardSpeed, angularSpeed);
        action.doAction(robot, simulationTimeStep);
    }

    void swerveRight(Entity &robot)
    {
        EntityAction action;

        const double forwardSpeed = 1.0;
        const double angularSpeed = 0.009;

        action = EntityAction(forwardSpeed, angularSpeed);
        action.doAction(robot, simulationTimeStep);
    }

    void turnLeft(Entity &robot)
    {
        EntityAction action;

        const double forwardSpeed = 1.0;
        const double angularSpeed = -0.0009;

        action = EntityAction(forwardSpeed, angularSpeed);
        action.doAction(robot, simulationTimeStep);
    }

    void swerveLeft(Entity &robot)
    {
        EntityAction action;

        const double forwardSpeed = 1.0;
        const double angularSpeed = -0.009;

        action = EntityAction(forwardSpeed, angularSpeed);
        action.doAction(robot, simulationTimeStep);
    }

    void takeAction(Entity &robot, int a)
    {
        if(a == 0)
        {
            moveForward(robot);
        }
        else if (a == 1)
        {
            turnRight(robot);
        }
        else if (a == 2)
        {
            swerveRight(robot);
        }
        else if (a == 3)
        {
            turnLeft(robot);
        }
        else if (a == 4)
        {
            swerveLeft(robot);
        }
    }

    Entity getRobot()
    {
        return world->getEntities("robot")[robotIndex];
    }

    void nextRobot()
    {
        //std::cout << "Current robotIndex is: " << robotIndex << std::endl;
        robotIndex++;
        //std::cout << "Next robotIndex is: " << robotIndex << std::endl;
        //std::cout << "Number of robots: " << world->getEntities("robot").size() << std::endl;
        if(robotIndex >= world->getEntities("robot").size())
        {
            robotIndex = 0;
            //std::cout << "robotIndex reset to 0" << std::endl;
        }
    }

    int getCollisions(Entity &robot)
    {
        return robot.getComponent<CSteer>().collisionCount;
    }

    void resetCollisions(Entity &robot)
    {
        robot.getComponent<CSteer>().collisionCount = 0;
    }

    std::vector<double> getSensorReadings(Entity &robot)
    { 
        std::vector<double> sensorReadings;
        for (int i = 0; i < robot.getComponent<CSensorArray>().obstacleSensors.size(); i++)
        {
            //std::cout << "sensor " << i << "output: " << robot.getComponent<CSensorArray>().obstacleSensors[i]->getReading(world) << std::endl;
            sensorReadings.push_back(robot.getComponent<CSensorArray>().obstacleSensors[i]->getReading(world));
        }
        return sensorReadings;
    }
};

void test()
{
    std::cout << "Lorem Ipsum" << std::endl;
}

PYBIND11_MODULE(control_bridge, m)
{
    m.doc() =   "A control inteface for setting up and running a cwaggle environment "
                "using python, the idea being that python commands can be used to call"
                "for the setup and rending of a cwaggle environment, and to control any "
                "robots/agents in the environment";

    m.def("test", &test);    

    py::class_<PybindControl>(m, "PybindControl")
        .def(py::init<>())
        .def("numberOfEntities", &PybindControl::numberOfEntities)
        .def("numberOfRobots", &PybindControl::numberOfRobots)
        .def("stepsPerRender", &PybindControl::getStepsPerRender)
        .def("simulatorUpdate", &PybindControl::simulatorUpdate)
        .def("makeGUI", &PybindControl::makeGUI)
        .def("updateGUI", &PybindControl::updateGUI)
        .def("moveForward", &PybindControl::moveForward)
        .def("getRobot", &PybindControl::getRobot)
        .def("nextRobot", &PybindControl::nextRobot)
        .def("turnRight", &PybindControl::turnRight)
        .def("takeAction", &PybindControl::takeAction)
        .def("isGUI", &PybindControl::isGUI)
        .def("getCollisions", &PybindControl::getCollisions)
        .def("getSensorReadings", &PybindControl::getSensorReadings)
        .def("resetCollisions", &PybindControl::resetCollisions);

    py::class_<Entity>(m, "Entity", py::dynamic_attr())
        .def(py::init<>())
        .def("id", &Entity::id)
        .def("isActive", &Entity::isActive)
        .def("setActive", &Entity::setActive)
        .def("tag", &Entity::tag);

}