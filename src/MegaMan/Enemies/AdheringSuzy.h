#ifndef ADHERINGSUZY_H
#define ADHERINGSUZY_H

#include <Enemy.h>

namespace mm {
class AdheringSuzy : public Enemy {
    public:
        AdheringSuzy(PlayableCharacter* player, Stage* stage);
        virtual ~AdheringSuzy();
        void Update(cgf::Game* game, bool updatePosition);

    protected:
        const static unsigned int IDLE = 1;
        const static unsigned int MOVE_LEFT = 2;
        const static unsigned int MOVE_RIGHT = 3;

        const float IDLE_TIME = 5;

        unsigned int currentState;
        unsigned int nextMove;
        float idleTimer;

        void Idle(cgf::Game* game);
        void Move(cgf::Game* game);

    private:
};
}

#endif // ADHERINGSUZY_H
