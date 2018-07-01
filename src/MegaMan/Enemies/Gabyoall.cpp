#include "Gabyoall.h"

mm::Gabyoall::Gabyoall(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition)
    : Enemy(player, stage, startPosition)
{
    sprite.load("content/enemies/gabyoall.png", 16, 8, 0, 0, 0, 0, 2, 1);
    currentState = STATE_MOVE_LEFT;

    moveSpeed = SPEED_FAR_FROM_PLAYER;

    sprite.setLooped(true);
    sprite.setFrameRange(0, 1);
    sprite.setAnimRate(ANIM_RATE_FAR_FROM_PLAYER);
    sprite.play();
}

mm::Gabyoall::~Gabyoall()
{
    //dtor
}

void mm::Gabyoall::Update(cgf::Game* game, bool updatePosition)
{
    float dx = this->GetPosition().x - player->GetPosition().x;
    float dy = this->GetPosition().y - player->GetPosition().y;
    float sqr_dist = dx * dx + dy * dy;
    if (sqr_dist < SQR_DISTANCE_FROM_PLAYER) {
        moveSpeed = SPEED_CLOSE_FROM_PLAYER;
        sprite.setAnimRate(ANIM_RATE_CLOSE_FROM_PLAYER);
    } else {
        moveSpeed = SPEED_FAR_FROM_PLAYER;
        sprite.setAnimRate(ANIM_RATE_FAR_FROM_PLAYER);
    }

    if (STATE_MOVE_LEFT == currentState) {
        sprite.setXspeed(-moveSpeed);
    } else if (STATE_MOVE_RIGHT == currentState) {
        sprite.setXspeed(moveSpeed);
    }
    // Apply movement and check for collisions
    unsigned int collision = stage->CheckCollision(COLLISION_LAYER, game, &sprite, true, false);
    if (collision != 0) {
        if (STATE_MOVE_LEFT == currentState && ((collision & Stage::LEFT_COLLISION) != 0 || (collision & Stage::LEFT_MAP_BOUND_COLLISION) != 0)) {
            currentState = STATE_MOVE_RIGHT;
        } else if (STATE_MOVE_RIGHT == currentState && ((collision & Stage::RIGHT_COLLISION) != 0 || (collision & Stage::RIGHT_MAP_BOUND_COLLISION) != 0)) {
            currentState = STATE_MOVE_LEFT;
        }
    }
    // Check for "ground" if I keep moving current direction
    if (STATE_MOVE_LEFT == currentState) {
        if(stage->GetCellFromMap(COLLISION_LAYER,
            sprite.getPosition().x - 1,
            sprite.getPosition().y + sprite.getSize().y + 1) == 0) {
            currentState = STATE_MOVE_RIGHT;
        }
    } else if (STATE_MOVE_RIGHT == currentState) {
        if(stage->GetCellFromMap(COLLISION_LAYER,
            sprite.getPosition().x + sprite.getSize().x + 1,
            sprite.getPosition().y + sprite.getSize().y + 1) == 0) {
            currentState = STATE_MOVE_LEFT;
        }
    }

    Entity::Update(game, false);
}
