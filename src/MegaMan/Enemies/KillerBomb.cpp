#include "KillerBomb.h"

mm::KillerBomb::KillerBomb(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition)
    : Enemy(player, stage, startPosition)
{
    sprite.load("content/enemies/killer-bomb.png", 16, 16, 0, 0, 0, 0, 1, 1);

    currentAngle = 0;
    verticalMoveSpeed = 3;
    movementAmplitude = 30;
    moveSpeed = -30;
}

mm::KillerBomb::~KillerBomb()
{
    //dtor
}

void mm::KillerBomb::Update(cgf::Game* game, bool updatePosition)
{
    float dt = game->getUpdateInterval() / 1000;
    currentAngle += verticalMoveSpeed * dt;
    if (currentAngle >= 180) {
        currentAngle -= 180;
    }

    float newX = sprite.getPosition().x + (moveSpeed * dt);
    float newY = startPosition.y + sin(currentAngle) * movementAmplitude;

    sprite.setPosition(newX, newY);

    Entity::Update(game, false);
}

// TODO: handle explosion
