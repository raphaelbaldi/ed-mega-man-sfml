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
    switch(currentState) {
    case STATE_GOING_UP:
        this->UpdatePosition(game);
        break;
    case EXPLODED:
        this->UpdateShoots(game);
        break;
    }
}

void mm::Bombombomb::UpdatePosition(cgf::Game* game)
{
}

void mm::Bombombomb::UpdateShoots(cgf::Game* game)
{
}
