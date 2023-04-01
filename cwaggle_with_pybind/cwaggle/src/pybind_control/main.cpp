
#include "CWaggle.h"

#include <sstream>
#include <iostream>



void testWorld()
{
    // create a world for use in python testing.
    // let's start with trying to recreate the orbital example
    //"auto world = ExampleWorlds::GetGetSquareWorld(800, 800, 20, 10, 250, 10);
    // GetGetSquareWorld(size_t width, size_t height, size_t numRobots, double robotSize, size_t numPucks, double puckSize)
    // width = height = 800
    // numRobots = 20
    // robotSize = 10
    // numPucks = 250
    // puckSize = 10

    // make the world
    auto world = std::make_shared<World>(800, 800);

    std::cout << "The Worlds Parameters are height: " << world->height() << " width: " << world->width() << std::endl;

    //add robots to the world
    for(size_t r = 0; r < 20; r++)
    {
        Entity robot = world->addEntity("robot");
        //std::cout << "robot id: " << robot.id() << std::endl;
        Vec2 rPos(rand() % 800, rand() % 800);
        robot.addComponent<CTransform>(rPos);
        robot.addComponent<CCircleBody>(10);
        robot.addComponent<CCircleShape>(10);
        robot.addComponent<CColor>(0, 100, 200, 255);
        robot.addComponent<CRobotType>(0);
    }

    world->update();
    std::cout << "There are " << world->getEntities("robot").size() << " Robots in the world" << std::endl;

    //add pucks to the world
    for(size_t p = 0; p < 250; p++)
    {
        int rWidth = rand() % 720;
        int rHeight = rand() % 720;
        Vec2 pPos(40 + rWidth, 40 + rHeight);

        Entity puck = world->addEntity("puck");
        puck.addComponent<CTransform>(pPos);
        puck.addComponent<CCircleBody>(10);
        puck.addComponent<CCircleShape>(10);
        puck.addComponent<CColor>(200, 44, 44, 255);
    }

    world->update();
    std::cout << "There are " << world->getEntities("puck").size() << " Pucks in the world" << std::endl;

    std::cout << "There are " << world->getEntities().size() << " Entities in the world" << std::endl;

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

    // for the orbital controller, here is where the controllers are added to the robots.
    // we will not be adding that here untill we have figured out a bit more about how the controllers tie in to everything.

    // create a simulator with the given world.
    auto simulator = std::make_shared<Simulator>(world);

    //set up the GUI
    GUI gui(simulator, 144);

    double simulationTimeStep = 1.0;

    double stepsPerRender = 1;

    // run the simulation and gui update() function in a loop
    while (true)
    {
        for (size_t i = 0; i < stepsPerRender; i++)
        {
            for (auto & robot : simulator->getWorld()->getEntities("robot"))
            {
                // if the entity doesn't have a controller we can skip it
                // right now that is all of them.
                if (!robot.hasComponent<CController>()) { continue; }
            }

            // call the world physics simulation update
            // parameter = how much sim time should pass (default 1.0)
            simulator->update(simulationTimeStep);
        }

        // if a gui exists, call for its display to update
        // note: simulation is limited by gui frame rate limit
        gui.update();
    }

    // the while loop above is what I need to had off to python, everythin else can be
    // done on the c++ side. So gui.update(), simulator->update(simulationTimeStep),
    // and the calls to the robots controller, which means a method to get the robot 
    // entities of the world, a method to recognize if the robot has an attached contrller,
    // and the action.doaction function. A step beyond that is figuring out how to let the
    // python side dictate the actiosn each robot will take. Maybe port over the EntityAction
    // class?
}


int main(int argc, char ** argv)
{
    testWorld();

    return 0;
}