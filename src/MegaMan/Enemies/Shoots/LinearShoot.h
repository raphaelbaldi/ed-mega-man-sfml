#ifndef LINEARSHOOT_H
#define LINEARSHOOT_H

#include <Entity.h>
#include "Game.h"

namespace mm
{
class LinearShoot : public Entity
{
    public:
        LinearShoot(sf::Vector2f startPosition, sf::Vector2f speed);
        virtual ~LinearShoot();
        void Update(cgf::Game* game, bool updatePosition);
        bool IsDestroyed();

    protected:

    private:
};
}

#endif // LINEARSHOOT_H
