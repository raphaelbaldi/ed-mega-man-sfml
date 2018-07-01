#include "AdheringSuzy.h"

mm::AdheringSuzy::AdheringSuzy(PlayableCharacter* player, Stage* stage)
    : Enemy(player, stage)
{
    sprite.load("content/enemies/adhering-suzy.png", 16, 16, 0, 0, 0, 0, 3, 1);

    currentState = IDLE;
    idleTimer = IDLE_TIME;
    nextMove = MOVE_RIGHT;

    moveSpeed = 120; // Faster than the player
}

mm::AdheringSuzy::~AdheringSuzy()
{
    //dtor
}

void mm::AdheringSuzy::Update(cgf::Game* game, bool updatePosition)
{
    switch(currentState) {
    case IDLE:
        this->Idle(game);
        break;
    default:
        this->Move(game);
        break;
    }
    Entity::Update(game, false);
}

void mm::AdheringSuzy::Idle(cgf::Game* game)
{
    idleTimer -= game->getUpdateInterval() / 1000;
    if (idleTimer <= 0) {
        // Last collision defines our next move.
        idleTimer = IDLE_TIME;
        currentState = nextMove;
    }
}

void mm::AdheringSuzy::Move(cgf::Game* game)
{
    if (MOVE_LEFT == currentState) {
        sprite.setXspeed(-moveSpeed);
    } else if (MOVE_RIGHT == currentState) {
        sprite.setXspeed(moveSpeed);
    }
    // Apply movement and check for collisions
    unsigned int collision = stage->CheckCollision(COLLISION_LAYER, game, &sprite, true, true);
    if (collision != 0) {
        if (MOVE_LEFT == currentState && (collision & Stage::LEFT_COLLISION) != 0) {
            nextMove = MOVE_RIGHT;
            currentState = IDLE;
        } else if (MOVE_RIGHT == currentState &&(collision & Stage::RIGHT_COLLISION) != 0) {
            nextMove = MOVE_LEFT;
            currentState = IDLE;
        }
    }
}
