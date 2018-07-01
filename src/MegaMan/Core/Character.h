#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"

namespace mm {
class Character : public Entity {
    public:
        Character(sf::Vector2f startPosition);
        virtual ~Character();

    protected:

    private:
};
}

#endif // CHARACTER_H
