#include "ScrewDriver.h"

mm::ScrewDriver::ScrewDriver(PlayableCharacter* player, Stage* stage)
    : Enemy(player, stage)
{
    sprite.load("content/enemies/mambu.png", 64, 16, 0, 0, 0, 0, 4, 1);
}

mm::ScrewDriver::~ScrewDriver()
{
    //dtor
}

void mm::ScrewDriver::Update(cgf::Game* game, bool updatePosition)
{
}
