#include "Bombombomb.h"

mm::Bombombomb::Bombombomb(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition)
    : Enemy(player, stage, startPosition)
{
    sprite.load("content/enemies/bombombomb.png", 16, 12, 0, 0, 0, 0, 1, 1);
    this->currentState = STATE_GOING_UP;
    this->moveSpeed = 140;
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
    case STATE_EXPLODED:
        this->UpdateShoots(game);
        break;
    }
}

void mm::Bombombomb::GenerateShoots(cgf::Game* game)
{

}

void mm::Bombombomb::UpdatePosition(cgf::Game* game)
{
    sprite.setYspeed(-moveSpeed);
    Entity::Update(game, true);

    if (abs(sprite.getPosition().y - startPosition.y) > MAX_DELTA_HEIGHT) {
        GenerateShoots(game);
        sprite.setVisible(false);
        currentState = STATE_EXPLODED;
    }
}

void mm::Bombombomb::UpdateShoots(cgf::Game* game)
{
}
