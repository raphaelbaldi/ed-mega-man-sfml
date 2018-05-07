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
            render(sf::RenderWindow* screen);

        protected:

        private:
    };
}

#endif // ENTITY_H
