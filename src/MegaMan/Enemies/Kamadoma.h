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
        const static unsigned int STATE_IDLE = 1;
        const static unsigned int STATE_JUMPING = 2;

        const float IDLE_TIME = 1.5;

        float idleTimer;

        void Idle(cgf::Game* game);
        void Jumping(cgf::Game* game);
        void ComputeJump(cgf::Game* game);


    private:
};
}

#endif // KAMADOMA_H
