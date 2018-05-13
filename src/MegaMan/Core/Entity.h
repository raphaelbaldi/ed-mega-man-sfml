#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"

namespace mm
{
    class Entity
    {
        public:
            Entity();
            virtual ~Entity();
            void render(sf::RenderWindow* screen);

        protected:
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
            int life;
            int totalLife;

        private:
    };
}

#endif // ENTITY_H
