#include "SniperJoe.h"

mm::SniperJoe::SniperJoe(PlayableCharacter* player, Stage* stage)
    : Enemy(player, stage)
{
    // TODO: organize sprites for Sniper Joe
    sprite.load("content/enemies/sniper-joe.png", 106, 31, 0, 0, 0, 0, 4, 1);
}

mm::SniperJoe::~SniperJoe()
{
    //dtor
}

void mm::SniperJoe::Update(cgf::Game* game, bool updatePosition)
{
}
