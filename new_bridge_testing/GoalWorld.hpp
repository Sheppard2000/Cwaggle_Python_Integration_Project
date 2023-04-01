
#include <vector>
#include "Vec2.hpp"

class World
{
    double width = 800;
    double height = 800;

public:
    World() {};
    World(double width, double height) : width(width), height(height) {};
};