#ifndef GABYOALL_H
#define GABYOALL_H

#include <Enemy.h>

namespace mm {
class Gabyoall : public Enemy {
    public:
        Gabyoall(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition);
        virtual ~Gabyoall();
        void Update(cgf::Game* game, bool updatePosition);

    protected:
        const static unsigned int STATE_MOVE_LEFT = 1;
        const static unsigned int STATE_MOVE_RIGHT = 2;

        const float SPEED_FAR_FROM_PLAYER = 50;
        const float SPEED_CLOSE_FROM_PLAYER = 100;

        const float ANIM_RATE_FAR_FROM_PLAYER = 2;
        const float ANIM_RATE_CLOSE_FROM_PLAYER = 4;

        const float SQR_DISTANCE_FROM_PLAYER = 9200;

    private:
};
}

#endif // GABYOALL_H
