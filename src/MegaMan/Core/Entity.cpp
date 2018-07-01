#include "Entity.h"

#include <iostream>

mm::Entity::Entity() {
    speed.x = 0;
    speed.y = 0;
    moveSpeed = 15;
    jumpSpeed = 15;
    currentJumpTime = 0;
    maxJumpTime = 1;
    fallSpeed = 15;
    bounceSpeed = 15;
    shootRate = 1;
    shootCooldown = 1;
    isTakingDamage = false;
    isJumping = false;
    isFalling = false;
    isAlive = true;
    isInvulnerable = false;
    isFacingLeft = false;
    isMoving = false;
    isShooting = false;
    currentAnimation = "";
    currentLife = 100;
    totalLife = 100;
}

mm::Entity::~Entity() {
}

void mm::Entity::Update(cgf::Game* game, bool updatePosition) {
    sprite.update(game->getUpdateInterval(), updatePosition);
    position.x = sprite.getPosition().x + sprite.getSize().x * 0.5;
    position.y = sprite.getPosition().y + sprite.getSize().y;
}

void mm::Entity::Render(sf::RenderWindow* screen) {
    Animate();
    screen->draw(sprite);
}

sf::Vector2f mm::Entity::GetPosition() {
    return position;
}

void mm::Entity::HandleEvents(cgf::InputManager* inputManager) {
}

void mm::Entity::SetAnimation(std::string newAnimation) {
    if(newAnimation.compare(currentAnimation) == 0) {
        return;
    }

    sprite.setAnimation(newAnimation);
    sprite.play();

    currentAnimation = newAnimation;
}

void mm::Entity::Animate() {
}

void mm::Entity::Shoot() {
}

bool mm::Entity::CanShoot() {
    return shootCooldown <= 0;
}
