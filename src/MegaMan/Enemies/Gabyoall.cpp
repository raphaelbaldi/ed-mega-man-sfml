#include "Gabyoall.h"

mm::Gabyoall::Gabyoall(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition)
    : Enemy(player, stage, startPosition)
{
    sprite.load("content/enemies/gabyoall.png", 32, 8, 0, 0, 0, 0, 2, 1);
}

mm::Gabyoall::~Gabyoall()
{
    //dtor
}

void mm::Gabyoall::Update(cgf::Game* game, bool updatePosition)
{
}
