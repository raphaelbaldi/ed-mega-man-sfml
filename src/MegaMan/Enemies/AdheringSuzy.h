#ifndef ADHERINGSUZY_H
#define ADHERINGSUZY_H

#include <Enemy.h>

namespace mm {
class AdheringSuzy : public Enemy {
    public:
        AdheringSuzy(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition);
        virtual ~AdheringSuzy();
        void Update(cgf::Game* game, bool updatePosition);

    protected:
        const static unsigned int STATE_IDLE = 1;
        const static unsigned int STATE_MOVE_LEFT = 2;
        const static unsigned int STATE_MOVE_RIGHT = 3;

        const float IDLE_TIME = 5;

        unsigned int nextMove;
        float idleTimer;

        void Idle(cgf::Game* game);
        void Move(cgf::Game* game);

    private:
};
}

#endif // ADHERINGSUZY_H
