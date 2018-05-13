#include "PlayableCharacter.h"

#include <iostream>

mm::PlayableCharacter::PlayableCharacter() {
    // TODO: make it configurable
    sprite.load("content/characters/megaman/megaman.png", 32, 32, 0, 0, 0, 0, 5, 4);

    sprite.loadAnimation("content/characters/megaman/megaman-animation.xml");
    sprite.setAnimRate(10);
    sprite.setMirror(!isFacingLeft);

    moveSpeed = 96;
    fallSpeed = 96;
    isClimbingStair = false;
    stage = nullptr;
}

mm::PlayableCharacter::~PlayableCharacter() {
}

void mm::PlayableCharacter::SetStage(mm::Stage* _stage) {
    stage = _stage;
}

void mm::PlayableCharacter::HandleEvents(cgf::InputManager* inputManager) {
    moveDirection.x = 0;
    moveDirection.y = 0;
    if(inputManager->testEvent("left")) {
        moveDirection.x = -1;
    } else if(inputManager->testEvent("right")) {
        moveDirection.x = 1;
    }

    if(inputManager->testEvent("up")) {
        moveDirection.y = -1;
    } else if(inputManager->testEvent("down")) {
        moveDirection.y = 1;
    }

    if(inputManager->testEvent("jump")) {
        isJumping = true;
    }

    if(inputManager->testEvent("shoot")) {
        Shoot();
        isShooting = true;
    } else {
        isShooting = false;
    }

    if(isTakingDamage) {
    } else {
        if(isClimbingStair) {
            sprite.setXspeed(0);
            sprite.setYspeed(moveDirection.y * moveSpeed);
        } else {
            sprite.setXspeed(moveDirection.x * moveSpeed);
            sprite.setYspeed(0);
        }
    }
}

void mm::PlayableCharacter::Animate() {
    bool wasFacingLeft = isFacingLeft;
    if(moveDirection.x > 0) {
        isFacingLeft = false;
    } else if(moveDirection.x < 0) {
        isFacingLeft = true;
    }
    if(wasFacingLeft != isFacingLeft) {
        sprite.setMirror(!isFacingLeft);
    }

    bool wasMoving = isMoving;
    isMoving = moveDirection.x != 0 || moveDirection.y != 0;

    // Default animation is idle
    std::string newAnimation = "idle";

    if(isTakingDamage) {
        newAnimation = "hit";
    } else {
        if(isJumping || isFalling) {
            if(isShooting) {
                newAnimation = "jump-shoot";
            } else {
                newAnimation = "jump";
            }
        } else {
            if(isClimbingStair) {
                if(isShooting) {
                    newAnimation = "stairs-shoot";
                } else {
                    newAnimation = "stairs";

                    if(wasMoving != isMoving) {
                        if(isMoving) {
                            sprite.play();
                        } else {
                            sprite.pause();
                        }
                    }
                }
            } else {
                if(moveDirection.x != 0) {
                    if(isShooting) {
                        newAnimation = "run-shoot";
                    } else {
                        newAnimation = "run";
                    }
                } else {
                    if(isShooting) {
                        newAnimation = "shoot";
                    } else {
                        newAnimation = "idle";
                    }
                }
            }
        }
    }

    /*
    TODO:
    "stairs-top"
    "idle-blink"
    */

    SetAnimation(newAnimation);
}

void mm::PlayableCharacter::Update(cgf::Game* game) {
    if(!IsGrounded()) {
        if(!isJumping && !isClimbingStair) {
            isFalling = true;
            fallSpeed += GRAVITY * game->getUpdateInterval();
            if(fallSpeed > maxFallSpeed) {
                fallSpeed = maxFallSpeed;
            }
            sprite.setYspeed(fallSpeed);
        }
    } else {
        isFalling = false;
        fallSpeed = 0;
    }

    Entity::Update(game);
}

bool mm::PlayableCharacter::IsGrounded() {
    if(nullptr == stage) {
        return false;
    }

    sf::Vector2f* charPosition = new sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + sprite.getSize().y);
    sf::Uint16 mapCell = stage->GetCellFromMap(COLLISION_LAYER, *charPosition);
    return mapCell != 0;
}

void mm::PlayableCharacter::Shoot() {
}

/*
SAMPLE CODE FOR COLLISION DETECTION
bool PlayState::checkCollision(uint8_t layer, cgf::Game* game, cgf::Sprite* obj) {
    int i, x1, x2, y1, y2;
    bool bump = false;

    // Get the limits of the map
    sf::Vector2u mapsize = map->GetMapSize();
    // Get the width and height of a single tile

    sf::Vector2u tilesize = map->GetMapTileSize();

    mapsize.x /= tilesize.x;
    mapsize.y /= tilesize.y;
    mapsize.x--;
    mapsize.y--;

    // Get the height and width of the object (in this case, 100% of a tile)
    sf::Vector2u objsize = obj->getSize();
    objsize.x *= obj->getScale().x;
    objsize.y *= obj->getScale().y;

    float px = obj->getPosition().x;
    float py = obj->getPosition().y;

    double deltaTime = game->getUpdateInterval();

    sf::Vector2f offset(obj->getXspeed()/1000 * deltaTime, obj->getYspeed()/1000 * deltaTime);

    float vx = offset.x;
    float vy = offset.y;

    // Test the horizontal movement first
    i = objsize.y > tilesize.y ? tilesize.y : objsize.y;

    for (;;)
    {
        x1 = (px + vx) / tilesize.x;
        x2 = (px + vx + objsize.x - 1) / tilesize.x;

        y1 = (py) / tilesize.y;
        y2 = (py + i - 1) / tilesize.y;

        if (x1 >= 0 && x2 < mapsize.x && y1 >= 0 && y2 < mapsize.y)
        {
            if (vx > 0)
            {
                // Trying to move right

                int upRight   = getCellFromMap(layer, x2*tilesize.x, y1*tilesize.y);
                int downRight = getCellFromMap(layer, x2*tilesize.x, y2*tilesize.y);
                if (upRight || downRight)
                {
                    // Place the player as close to the solid tile as possible
                    px = x2 * tilesize.x;
                    px -= objsize.x;// + 1;
                    vx = 0;
                    bump = true;
                }
            }

            else if (vx < 0)
            {
                // Trying to move left

                int upLeft   = getCellFromMap(layer, x1*tilesize.x, y1*tilesize.y);
                int downLeft = getCellFromMap(layer, x1*tilesize.x, y2*tilesize.y);
                if (upLeft || downLeft)
                {
                    // Place the player as close to the solid tile as possible
                    px = (x1+1) * tilesize.x;
                    vx = 0;
                    bump = true;
                }
            }
        }

        if (i == objsize.y) // Checked player height with all tiles ?
        {
            break;
        }

        i += tilesize.y; // done, check next tile upwards

        if (i > objsize.y)
        {
            i = objsize.y;
        }
    }

    // Now test the vertical movement
    i = objsize.x > tilesize.x ? tilesize.x : objsize.x;

    for (;;)
    {
        x1 = (px / tilesize.x);
        x2 = ((px + i-1) / tilesize.x);

        y1 = ((py + vy) / tilesize.y);
        y2 = ((py + vy + objsize.y-1) / tilesize.y);

        if (x1 >= 0 && x2 < mapsize.x && y1 >= 0 && y2 < mapsize.y)
        {
            if (vy > 0)
            {
                // Trying to move down
                int downLeft  = getCellFromMap(layer, x1*tilesize.x, y2*tilesize.y);
                int downRight = getCellFromMap(layer, x2*tilesize.x, y2*tilesize.y);
                if (downLeft || downRight)
                {
                    // Place the player as close to the solid tile as possible
                    py = y2 * tilesize.y;
                    py -= objsize.y;
                    vy = 0;
                    bump = true;
                }
            }

            else if (vy < 0)
            {
                // Trying to move up

                int upLeft  = getCellFromMap(layer, x1*tilesize.x, y1*tilesize.y);
                int upRight = getCellFromMap(layer, x2*tilesize.x, y1*tilesize.y);
                if (upLeft || upRight)
                {
                    // Place the player as close to the solid tile as possible
                    py = (y1 + 1) * tilesize.y;
                    vy = 0;
                    bump = true;
                }
            }
        }

        if (i == objsize.x)
        {
            break;
        }

        i += tilesize.x; // done, check next tile to the right

        if (i > objsize.x)
        {
            i = objsize.x;
        }
    }

    // Now apply the movement and animation

    obj->setPosition(px+vx,py+vy);
    px = obj->getPosition().x;
    py = obj->getPosition().y;

    obj->update(deltaTime, false); // only update animation

    // Check collision with edges of map
    if (px < 0)
        obj->setPosition(px,py);
    else if (px + objsize.x >= mapsize.x * tilesize.x)
        obj->setPosition(mapsize.x*tilesize.x - objsize.x - 1,py);

    if(py < 0)
        obj->setPosition(px,0);
    else if(py + objsize.y >= mapsize.y * tilesize.y)
        obj->setPosition(px, mapsize.y*tilesize.y - objsize.y - 1);

    return bump;
}
*/
