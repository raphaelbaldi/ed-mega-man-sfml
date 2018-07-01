#include "LinearShoot.h"

#include <iostream>

mm::LinearShoot::LinearShoot(sf::Vector2f startPosition, sf::Vector2f speed)
    : Entity(startPosition)
{
    sprite.load("content/shoots/blue-shoot.png", 6, 6, 0, 0, 0, 0, 1, 1);
    sprite.setXspeed(speed.x);
    sprite.setYspeed(speed.y);
}

mm::LinearShoot::~LinearShoot()
{
    //dtor
}

bool mm::LinearShoot::IsDestroyed()
{
    return false;
}

void mm::LinearShoot::Update(cgf::Game* game, bool updatePosition)
{
    Entity::Update(game, updatePosition);
}
