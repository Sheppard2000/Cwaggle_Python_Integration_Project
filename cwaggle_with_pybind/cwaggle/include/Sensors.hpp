#pragma once

#include <float.h>
#include <string>
using std::string;

#include "Components.hpp"
#include "Entity.hpp"
#include "World.hpp"

class Sensor {
protected:
    size_t m_ownerID; // entity that owns this sensor
    string m_name;
    double m_angle = 0; // angle sensor is placed w.r.t. owner heading
    double m_distance = 0; // distance from center of owner

public:
    Sensor() { }
    Sensor(size_t ownerID, string name, double angle, double distance)
        : m_ownerID(ownerID)
        , m_name(name)
        , m_angle(angle * M_PI / 180.0)
        , m_distance(distance)
    {
    }

    inline string name() const
    {
        return m_name;
    }

    inline virtual Vec2 getPosition()
    {
        const Vec2& pos = Entity(m_ownerID).getComponent<CTransform>().p;
        double sumAngle = m_angle + Entity(m_ownerID).getComponent<CSteer>().angle;
        return pos + Vec2(m_distance * cos(sumAngle), m_distance * sin(sumAngle));
    }

    inline virtual double angle() const
    {
        return m_angle;
    }

    inline virtual double distance() const
    {
        return m_distance;
    }

    virtual double getReading(std::shared_ptr<World> world) = 0;
};

class GridSensor : public Sensor {
public:
    size_t m_gridIndex;

    GridSensor(size_t ownerID, string name, size_t gridIndex, double angle, double distance)
        : Sensor(ownerID, name, angle, distance)
    {
        m_gridIndex = gridIndex;
    }

    inline virtual double getReading(std::shared_ptr<World> world)
    {
        if (world->getGrid(m_gridIndex).width() == 0) {
            return 0;
        }
        Vec2 sPos = getPosition();
        size_t gX = (size_t)round(world->getGrid(m_gridIndex).width() * sPos.x / world->width());
        size_t gY = (size_t)round(world->getGrid(m_gridIndex).height() * sPos.y / world->height());
        return world->getGrid(m_gridIndex).get(gX, gY);
    }
};

class RobotSensor : public Sensor
{
public:
    double m_radius;

    RobotSensor(size_t ownerID, string name, double angle, double distance, double radius)
        : Sensor(ownerID, name, angle, distance)
    {
        m_radius = radius;
    }

    inline double getReading(std::shared_ptr<World> world)
    {
        double sum = 0;
        Vec2 pos = getPosition();
        for (auto e : world->getEntities())
        {
            if (!e.hasComponent<CSteer>()) { continue; }
            if (m_ownerID == e.id()) { continue; }

            auto & t = e.getComponent<CTransform>();
            auto & b = e.getComponent<CCircleBody>();

            // collision with other robot
            if (t.p.distSq(pos) < (m_radius + b.r)*(m_radius + b.r))
            {
                sum += 1.0;
            }
        }
        return sum;
    }

    inline double radius() const
    {
        return m_radius;
    }
};

class PuckSensor : public Sensor
{
    double m_radius;

public:

    PuckSensor(size_t ownerID, string name, double angle, double distance, double radius)
        : Sensor(ownerID, name, angle, distance)
    {
        m_radius = radius;
    }

    inline double getReading(std::shared_ptr<World> world)
    {
        double sum = 0;
        Vec2 pos = getPosition();
        for (auto puck : world->getEntities("puck"))
        {
            auto & t = puck.getComponent<CTransform>();
            auto & b = puck.getComponent<CCircleBody>();

            // collision with a puck
            if (t.p.distSq(pos) < (m_radius + b.r)*(m_radius + b.r))
            {
                sum += 1.0;
            }
        }
        return sum;
    }

    inline double radius() const
    {
        return m_radius;
    }

};

class ObstacleSensor : public Sensor
{
    double m_radius;

public:

    ObstacleSensor(size_t ownerID, string name, double angle, double distance, double radius)
        : Sensor(ownerID, name, angle, distance)
    {
        m_radius = radius;
    }

    inline double getReading(std::shared_ptr<World> world)
    {
        double sum = 0;
        Vec2 pos = getPosition();
        for (auto e : world->getEntities())
        {
            if (!e.hasComponent<CCircleBody>()) { continue; }
            if (m_ownerID == e.id()) { continue; }

            auto & t = e.getComponent<CTransform>();
            auto & b = e.getComponent<CCircleBody>();

            // collision with a puck
            if (t.p.distSq(pos) < (m_radius + b.r)*(m_radius + b.r))
            {
                sum += 1.0;
            }
        }
        // added in wall/world boundings detection
        if (pos.x - m_radius <= 0 || pos.x + m_radius >= world->width() || pos.y - m_radius <= 0 || pos.y >= world->height())
        {
            sum += 1.0;
        }
        return sum;
    }

    inline double radius() const
    {
        return m_radius;
    }
};

/*
// check for collisions with the bounds of the world
            if (t1.p.x - b1.r < 0) 
            { 
                t1.p.x = b1.r; 
                b1.collided = true;
                // TS: extra bit to count collisions with the bounds of the world
                if (e1.hasComponent<CSteer>())
                {
                    e1.getComponent<CSteer>().collisionCount++;
                }
            }
            if (t1.p.y - b1.r < 0) 
            { 
                t1.p.y = b1.r; 
                b1.collided = true;
                if (e1.hasComponent<CSteer>())
                {
                    e1.getComponent<CSteer>().collisionCount++;
                }
            }
            if (t1.p.x + b1.r > m_world->width()) 
            { 
                t1.p.x = m_world->width() - b1.r;  
                b1.collided = true; 
                // TS: extra bit to count collisions with the bounds of the world
                if (e1.hasComponent<CSteer>())
                {
                    e1.getComponent<CSteer>().collisionCount++;
                }
            }
            if (t1.p.y + b1.r > m_world->height()) 
            { 
                t1.p.y = m_world->height() - b1.r; 
                b1.collided = true;
                // TS: extra bit to count collisions with the bounds of the world
                if (e1.hasComponent<CSteer>())
                {
                    e1.getComponent<CSteer>().collisionCount++;
                }
            }
*/
