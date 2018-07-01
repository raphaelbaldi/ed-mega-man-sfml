#ifndef ENTITY_H
#define ENTITY_H

#include "Game.h"
#include "Sprite.h"
#include "InputManager.h"

namespace mm {
class Entity {
    public:
        Entity(sf::Vector2f startPosition);
        virtual ~Entity();
        virtual void Render(sf::RenderWindow* screen);
        virtual void Update(cgf::Game* game, bool updatePosition);
        virtual void HandleEvents(cgf::InputManager* inputManager);
        sf::Vector2f GetPosition();
        virtual bool IsAlive();

    protected:
        cgf::Sprite sprite;
        sf::Vector2f speed;
        sf::Vector2f position;
        std::string currentAnimation;
        float moveSpeed;
        float jumpSpeed;
        float currentJumpTime;
        float maxJumpTime; // Hold jump to jump higher
        float fallSpeed;
        float bounceSpeed;
        float shootRate;
        float shootCooldown;
        bool isTakingDamage;
        bool isJumping;
        bool isFalling;
        bool isAlive;
        bool isInvulnerable;
        bool isFacingLeft;
        bool isMoving;
        bool isShooting;
        int currentLife;
        int totalLife;
        sf::Vector2f startPosition;

        virtual void Animate();
        virtual void Shoot();
        void SetAnimation(std::string newAnimation);
        bool CanShoot();

    private:
};
}

#endif // ENTITY_H
