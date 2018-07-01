#include "Bombombomb.h"

mm::Bombombomb::Bombombomb(PlayableCharacter* player, Stage* stage)
    : Enemy(player, stage)
{
    sprite.load("content/enemies/bombombomb.png", 1, 12, 0, 0, 0, 0, 1, 1);
}

mm::Bombombomb::~Bombombomb()
{
    //dtor
}

void mm::Bombombomb::Update(cgf::Game* game, bool updatePosition)
{
}
