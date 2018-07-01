#ifndef SCREWDRIVER_H
#define SCREWDRIVER_H

#include <Enemy.h>

namespace mm {
class ScrewDriver : public Enemy {
    public:
        ScrewDriver(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition);
        virtual ~ScrewDriver();
        void Update(cgf::Game* game, bool updatePosition);

    protected:

    private:
};
}

#endif // SCREWDRIVER_H
