#ifndef PARTICLE_2D_H
#define PARTICLE_2D_H

#include <vector>
#include "mathLib2D.h"

class particle2D{
    public:
    Point2D position;
    Vec2D direction;
    Vec2D acceleration;
    Vec2D velocity;
    std::vector<float> colour;
    float size;
    float range;
    float force;
    float decay;
    
    particle2D(Point2D position, Vec2D direction, std::vector<float> colour, float size, float range, Vec2D acceleration, Vec2D velocity, float decay);
    void setAcceleration(float x, float y, float baseRange, bool isAttracted, float force);
    void updateAcceleration(Vec2D force);
    void move(int xBound, int yBound, float baseSpeed);
};

#endif