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
            sf::Vector2f position;
            sf::Vector2f moveDirection;
            float moveSpeed;
            float jumpSpeed;
            float fallSpeed;
            float bounceSpeed;
            bool takingDamage;
            bool isJumping;
            bool isFalling;
            bool isAlive;
            bool isInvulnerable;
            bool isMovingLeft;
            int life;
            int totalLife;

        private:
    };
}

#endif // ENTITY_H
