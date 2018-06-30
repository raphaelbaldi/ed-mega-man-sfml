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
    jumpSpeed = 96;
    maxJumpTime = 0.6;
    isClimbingStair = false;
    jumpPressed = false;
    stage = nullptr;

    moveDirection.x = 0;
    moveDirection.y = 0;

    rectangle = new sf::RectangleShape(sf::Vector2f(sprite.getSize().x, sprite.getSize().y));
    rectangle->setFillColor(sf::Color(255, 0, 0));
}

void mm::PlayableCharacter::Render(sf::RenderWindow* window) {
    mm::Entity::Render(window);
    rectangle->setPosition(sprite.getPosition());
    //window->draw(*rectangle);
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
        if(!isFalling && !isTakingDamage && !isClimbingStair && !jumpPressed) {
            jumpPressed = true;
            if(!isJumping) {
                isJumping = true;
                currentJumpTime = maxJumpTime;
            }
        }
    } else {
        jumpPressed = false;
        if(isJumping) {
            isJumping = false;
        }
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

void mm::PlayableCharacter::Update(cgf::Game* game, bool updatePosition) {
    sprite.setXspeed(moveDirection.x * moveSpeed);

    // Update Jump
    if(isJumping) {
        sprite.setYspeed(-jumpSpeed);
        currentJumpTime -= game->getUpdateInterval() / 1000;
        if(currentJumpTime <= 0) {
            isJumping = false;
        }
    }

    if(nullptr != stage) {
        unsigned int collisionResult = stage->CheckCollision(COLLISION_LAYER, game, &sprite);

        // Control fall;
        if ((collisionResult & Stage::DOWN_COLLISION) != 0) {
            isFalling = false;
        } else {
            if(!isJumping && !isClimbingStair) {
                isFalling = true;
                sprite.setYspeed(fallSpeed);
            }
        }
    }

    Entity::Update(game, false);
}

void mm::PlayableCharacter::Shoot() {
}
