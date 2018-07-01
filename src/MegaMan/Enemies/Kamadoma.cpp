#include "Kamadoma.h"

mm::Kamadoma::Kamadoma(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition)
    : Enemy(player, stage, startPosition)
{
    sprite.load("content/enemies/kamadoma.png", 14, 19, 0, 0, 0, 0, 2, 1);

    currentState = STATE_IDLE;
    idleTimer = IDLE_TIME;

    moveSpeed = 70;
    jumpSpeed = 100;
}

mm::Kamadoma::~Kamadoma()
{
    //dtor
}

void mm::Kamadoma::Update(cgf::Game* game, bool updatePosition)
{
    switch(currentState) {
    case STATE_IDLE:
        this->Idle(game);
        break;
    default:
        this->Jumping(game);
        break;
    }
    Entity::Update(game, false);
}

void mm::Kamadoma::Idle(cgf::Game* game)
{
    idleTimer -= game->getUpdateInterval() / 1000;
    sprite.setCurrentFrame(0);
    if (idleTimer <= 0) {
        // Last collision defines our next move.
        idleTimer = IDLE_TIME;
        ComputeJump(game);
        currentState = STATE_JUMPING;
    }
}

void mm::Kamadoma::Jumping(cgf::Game* game)
{
    float currentYSpeed = sprite.getYspeed();
    currentYSpeed += GRAVITY * game->getUpdateInterval() / 1000;
    sprite.setYspeed(currentYSpeed);

    unsigned int collision = stage->CheckCollision(COLLISION_LAYER, game, &sprite, true, true);
    if ((collision & Stage::DOWN_COLLISION) != 0 || (collision & Stage::DOWN_MAP_BOUND_COLLISION) != 0) {
        currentState = STATE_IDLE;
        sprite.setCurrentFrame(0);
    } else {
        sprite.setCurrentFrame(1);
    }
}

void mm::Kamadoma::ComputeJump(cgf::Game* game)
{
    //float dx = abs(player->GetPosition().x - GetPosition().x);
    //float timeToReachPlayer = dx / moveSpeed;
    //float timeToReachHighestY = timeToReachPlayer / 2;

    sprite.setYspeed(-jumpSpeed);
    if (player->GetPosition().x > GetPosition().x) {
        sprite.setXspeed(moveSpeed);
    } else {
        sprite.setXspeed(-moveSpeed);
    }
}
