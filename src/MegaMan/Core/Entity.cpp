#include "Entity.h"

#include <iostream>

mm::Entity::Entity() {
    moveDirection.x = 0;
    moveDirection.y = 0;
    moveSpeed = 15;
    jumpSpeed = 15;
    currentJumpTime = 0;
    maxJumpTime = 1;
    fallSpeed = 9.8;
    bounceSpeed = 15;
    shootRate = 1;
    shootCooldown = 0.2;
    isTakingDamage = false;
    isJumping = false;
    isFalling = false;
    isAlive = true;
    isInvulnerable = false;
    isFacingLeft = false;
    isMoving = false;
    life = 100;
    totalLife = 100;
}

mm::Entity::~Entity() {
}

void mm::Entity::Update(cgf::Game* game) {
    sprite.update(game->getUpdateInterval());
    position.x = sprite.getPosition().x + sprite.getSize().x / 2;
    position.y = sprite.getPosition().y;
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

void mm::Entity::Animate() {
}

void mm::Entity::Shoot() {
}

bool mm::Entity::CanShoot() {
    return shootCooldown <= 0;
}
