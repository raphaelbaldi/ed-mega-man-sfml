#ifndef KILLERBOMB_H
#define KILLERBOMB_H

#include <Enemy.h>

namespace mm {
class KillerBomb : public Enemy {
    public:
        KillerBomb(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition);
        virtual ~KillerBomb();
        void Update(cgf::Game* game, bool updatePosition);

    protected:

    private:
};
}

#endif // KILLERBOMB_H