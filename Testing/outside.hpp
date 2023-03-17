#include "tracker.hpp"
#include <iostream>

std::string message = "I am from the outside";

Tracker OutsideMan;

class pet
{
    friend class EntityMemoryPool;

protected:
    double age;
    double birthday;

public:
    pet(double age, double birthday)
        : age(age)
        , birthday(birthday) {}
    void getStats()
    {
        std::cout << "Age: " << age << " Birthday: " << birthday << std::endl;
    }
};

void printMessage()
{
    std::cout << message << std::endl;
}

void newTracker(int id, std::string name, int xpos, int ypos)
{
    OutsideMan = Tracker(id, name, Vec2(xpos, ypos));
}

int getID()
{
    return OutsideMan.id;
}

std::string getName()
{
    return OutsideMan.name;
}

int getPosX()
{
    return OutsideMan.pos.x;
}

int getPosY()
{
    return OutsideMan.pos.y;
}

void updatePos(int nPosX, int nPosY)
{
    OutsideMan.pos = Vec2(nPosX, nPosY);
}

void updateID(std::string newName)
{
    OutsideMan.name = newName;
}
