#include "Enemy.h"

mm::Enemy::Enemy(PlayableCharacter* player, Stage* stage)
{
    //ctor
    this->player = player;
    this->stage = stage;
}

mm::Enemy::~Enemy()
{
    //dtor
}
