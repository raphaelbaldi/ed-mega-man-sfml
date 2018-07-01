#ifndef KAMADOMA_H
#define KAMADOMA_H

#include <Enemy.h>

namespace mm {
class Kamadoma : public Enemy {
    public:
        Kamadoma(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition);
        virtual ~Kamadoma();
        void Update(cgf::Game* game, bool updatePosition);

    protected:

    private:
};
}

#endif // KAMADOMA_H
