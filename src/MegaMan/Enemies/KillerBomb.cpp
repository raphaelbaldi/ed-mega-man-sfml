#include "KillerBomb.h"

mm::KillerBomb::KillerBomb(PlayableCharacter* player, Stage* stage)
    : Enemy(player, stage)
{
    sprite.load("content/enemies/gabyoall.png", 16, 16, 0, 0, 0, 0, 1, 1);
}

mm::KillerBomb::~KillerBomb()
{
    //dtor
}

void mm::KillerBomb::Update(cgf::Game* game, bool updatePosition)
{
}
