#include "PlayableCharacter.h"

#include <iostream>

mm::PlayableCharacter::PlayableCharacter() {
    // TODO: make it configurable
    sprite.load("content/characters/megaman/megaman.png", 32, 32, 0, 0, 0, 0, 5, 4);

    sprite.loadAnimation("content/characters/megaman/megaman-animation.xml");
    sprite.setAnimRate(10);
    sprite.setAnimation("idle");
    sprite.play();
    sprite.setMirror(!isFacingLeft);

    moveSpeed = 96;
    isClimbingStair = false;
}

mm::PlayableCharacter::~PlayableCharacter() {
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
    }

    if(isTakingDamage) {
        // Player has no control over movement
    } else {
        if(isClimbingStair) {
            // If climbing stair, can only move vertically
            moveDirection.x = 0;
        } else {
            moveDirection.y = 0;
        }
    }

    sprite.setXspeed(moveDirection.x * moveSpeed);
    sprite.setYspeed(moveDirection.y * moveSpeed);
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

    if(wasMoving != isMoving) {

        if(!isMoving) {
            sprite.setAnimation("idle");
        } else {
            sprite.setLooped(true);
            sprite.setAnimation("run");
        }
        sprite.setLooped(true);
        sprite.play();
    }
}

void mm::PlayableCharacter::Shoot() {
}
