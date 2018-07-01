#include "Enemy.h"

mm::Enemy::Enemy(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition)
    : Entity(startPosition)
{
    //ctor
    this->player = player;
    this->stage = stage;
}

mm::Enemy::~Enemy()
{
    //dtor
}
