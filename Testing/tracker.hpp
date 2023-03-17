#include <vector>
#include <string>
#include "Vec2.hpp"

class Tracker 
{
    public:
        int id = 0;
        std::string name = "name";
        Vec2 pos = Vec2();
        Tracker() {};
        Tracker(int id_in, std::string n_in)
        : id(id_in)
        , name(n_in) { };
        Tracker(int id_in, std::string n_in, Vec2 p_in)
        : id(id_in)
        , name(n_in)
        , pos(p_in) { };
};