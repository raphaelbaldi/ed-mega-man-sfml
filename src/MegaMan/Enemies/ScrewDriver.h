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
        const static unsigned int STATE_IDLE = 1;
        const static unsigned int STATE_SHOOTING = 2;

        const float SHOOT_SPEED = 50;

        const float ANIMATION_SPEED = 3;

        const float IDLE_TIME = 3;
        const float SHOOT_TIME = 5;

        const static unsigned int SHOOTS_PER_SPAWN = 2;

        float idleTimer;
        float shootTimer;
        unsigned int shootCounter;

        void Idle(cgf::Game* game);
        void Shooting(cgf::Game* game);
        void GenerateShoots(cgf::Game* game);
        void ControlShoots(cgf::Game* game);

    private:
};
}

#endif // SCREWDRIVER_H
