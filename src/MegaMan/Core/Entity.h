#ifndef ENTITY_H
#define ENTITY_H

#include "Game.h"
#include "Sprite.h"
#include "InputManager.h"

namespace mm
{
    class Entity
    {
        public:
            Entity();
            virtual ~Entity();
            virtual void Render(sf::RenderWindow* screen);
            virtual void Update(cgf::Game* game);
            virtual void HandleEvents(cgf::InputManager* inputManager);
            sf::Vector2f GetPosition();

        protected:
            cgf::Sprite sprite;
            sf::Vector2f moveDirection;
            sf::Vector2f position;
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
            int life;
            int totalLife;

            virtual void Animate();
            bool CanShoot();
            virtual void Shoot();

        private:
    };
}

#endif // ENTITY_H
