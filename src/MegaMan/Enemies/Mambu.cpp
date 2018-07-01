#include "Mambu.h"

mm::Mambu::Mambu(PlayableCharacter* player, Stage* stage)
    : Enemy(player, stage)
{
    sprite.load("content/enemies/mambu.png", 34, 21, 0, 0, 0, 0, 2, 1);
}

mm::Mambu::~Mambu()
{
    //dtor
}

void mm::Mambu::Update(cgf::Game* game, bool updatePosition)
{
}
