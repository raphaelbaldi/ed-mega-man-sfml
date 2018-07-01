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
        bool IsOnScreen(cgf::Game* game);
        virtual bool IsDestroyed();

    protected:
        const float GRAVITY = 120;

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
        float shotRate;
        float shotCooldown;
        bool isTakingDamage;
        bool isJumping;
        bool isFalling;
        bool isAlive;
        bool isInvulnerable;
        bool isFacingLeft;
        bool isMoving;
        bool isShoting;
        int currentLife;
        int totalLife;
        sf::Vector2f startPosition;

        void SetAnimation(std::string newAnimation);
        virtual void Animate();

    private:
};
}

#endif // ENTITY_H
