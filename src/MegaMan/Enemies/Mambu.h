#ifndef MAMBU_H
#define MAMBU_H

#include <Enemy.h>

namespace mm {
class Mambu : public Enemy {
    public:
        Mambu(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition);
        virtual ~Mambu();
        void Update(cgf::Game* game, bool updatePosition);

    protected:

    private:
};
}

#endif // MAMBU_H
