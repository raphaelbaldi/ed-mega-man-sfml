#include "Kamadoma.h"

mm::Kamadoma::Kamadoma(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition)
    : Enemy(player, stage, startPosition)
{
    sprite.load("content/enemies/kamadoma.png", 28, 19, 0, 0, 0, 0, 2, 1);
}

mm::Kamadoma::~Kamadoma()
{
    //dtor
}

void mm::Kamadoma::Update(cgf::Game* game, bool updatePosition)
{
}
