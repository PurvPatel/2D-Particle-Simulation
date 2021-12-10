#include "particle2D.h"
#include <iostream>
particle2D::particle2D(Point2D position, Vec2D direction, std::vector<float> colour, float size, float range, Vec2D acceleration, Vec2D velocity, float decay){
    this->position = position;
    this->direction = direction;
    this->colour = colour;
    this->size = size;
    this->range = range;
    this->acceleration = acceleration;
    this->decay = decay;
    this->velocity = velocity;
}

void particle2D::setAcceleration(float x, float y, float baseRange, bool isAttracted, float force){
    // check if particle in range
    if (this->position.fastDistanceTo(Point2D(x, y)) <= (this->range + baseRange)){

        //if in range, set vector
        this->direction = Vec2D::createVector(this->position, Point2D(x, y)).normalize();
        if (!isAttracted){
            this->direction.mX = - this->direction.mX;
            this->direction.mY = - this->direction.mY;
        }
        this->acceleration.mX = this->direction.mX * force / this->size;
        this->acceleration.mY = this->direction.mY * force / this->size;
    }
}

void particle2D::updateAcceleration(Vec2D force){
    Vec2D accelerationUpdate(force.mX, force.mY);
    this->acceleration = this->acceleration.add(accelerationUpdate);
    return;
}
void particle2D::move(int xBound, int yBound, float baseSpeed){


    // keeping particles bounded in window
    if(this->position.mX <= 0 || this->position.mX >= xBound){
        this->direction.mX = - this->direction.mX;
        this->velocity.mX = - this->velocity.mX;
        this->acceleration.mX = - this->acceleration.mX;
    }

    if(this->position.mY <= 0 || this->position.mY >= yBound){
        this->direction.mY = - this->direction.mY;
        this->velocity.mY = - this->velocity.mY;
        this->acceleration.mY = - this->acceleration.mY;
    }

    // update velocity and position
    this->velocity = this->velocity.add(this->acceleration);
    if (this->velocity.mX == 0.0f && this->velocity.mY == 0.0f)
        return;

    //move particle
    this->position = this->velocity.movePoint(this->position, baseSpeed);

    //assumed acceleration is zero
    this->acceleration.mX = 0;
    this->acceleration.mY = 0;

    //decay speed over time since there is no friction force
    this->velocity.mX -= this->decay * this->velocity.mX;
    this->velocity.mY -= this->decay * this->velocity.mY;


}