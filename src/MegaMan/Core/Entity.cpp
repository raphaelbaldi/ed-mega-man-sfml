#include "Entity.h"

#include <iostream>

mm::Entity::Entity(sf::Vector2f startPosition)
{
    speed.x = 0;
    speed.y = 0;
    moveSpeed = 15;
    jumpSpeed = 15;
    currentJumpTime = 0;
    maxJumpTime = 1;
    fallSpeed = 15;
    bounceSpeed = 15;
    shotRate = 1;
    shotCooldown = 1;
    isTakingDamage = false;
    isJumping = false;
    isFalling = false;
    isAlive = true;
    isInvulnerable = false;
    isFacingLeft = false;
    isMoving = false;
    isShoting = false;
    currentAnimation = "";
    currentLife = 100;
    totalLife = 100;
    sprite.setPosition(startPosition);
    this->startPosition.x = startPosition.x;
    this->startPosition.y = startPosition.y;
}

mm::Entity::~Entity()
{
}

bool mm::Entity::IsAlive()
{
    return true;
}

void mm::Entity::Update(cgf::Game* game, bool updatePosition)
{
    sprite.update(game->getUpdateInterval(), updatePosition);
    position.x = sprite.getPosition().x + sprite.getSize().x * 0.5;
    position.y = sprite.getPosition().y + sprite.getSize().y * 0.5;
}

void mm::Entity::Render(sf::RenderWindow* screen)
{
    Animate();
    screen->draw(sprite);
}

sf::Vector2f mm::Entity::GetPosition()
{
    return position;
}

void mm::Entity::HandleEvents(cgf::InputManager* inputManager)
{
}

void mm::Entity::Animate()
{
}

void mm::Entity::SetAnimation(std::string newAnimation)
{
    if(newAnimation.compare(currentAnimation) == 0) {
        return;
    }

    sprite.setAnimation(newAnimation);
    sprite.play();

    currentAnimation = newAnimation;
}

bool mm::Entity::IsOnScreen(cgf::Game* game)
{
    if (nullptr == game) {
        return true;
    }

    sf::View view = game->getScreen()->getView();

    sf::Vector2u spriteSize = sprite.getSize();
    spriteSize.x *= sprite.getScale().x;
    spriteSize.y *= sprite.getScale().y;

    float viewWSize = view.getSize().x / 2;
    float viewVSize = view.getSize().y / 2;
    if (sprite.getPosition().x + spriteSize.x < view.getCenter().x - viewWSize ||
        sprite.getPosition().x > view.getCenter().x + viewWSize ||
        sprite.getPosition().y + spriteSize.y < view.getCenter().y - viewVSize ||
        sprite.getPosition().y > view.getCenter().y + viewVSize) {
            return false;
    }

    return true;
}

bool mm::Entity::IsDestroyed()
{
    return false;
}
