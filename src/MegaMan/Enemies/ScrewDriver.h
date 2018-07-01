#ifndef SCREWDRIVER_H
#define SCREWDRIVER_H

#include <Enemy.h>
#include <math.h>
#include "Shoots/LinearShoot.h"

namespace mm {
class ScrewDriver : public Enemy {
    public:
        ScrewDriver(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition);
        virtual ~ScrewDriver();
        void Update(cgf::Game* game, bool updatePosition);
        void Render(sf::RenderWindow* screen);

    protected:
        const static unsigned int STATE_IDLE = 1;
        const static unsigned int STATE_SHOOTING = 2;

        const float SHOOT_SPEED = 80;

        const float ANIMATION_SPEED = 3;

        const float IDLE_TIME = 3;
        const float SHOOT_TIME = 5;

        const static unsigned int SHOTS_PER_SPAWN = 2;

        float idleTimer;
        float shotTimer;
        unsigned int shotCounter;

        void Idle(cgf::Game* game);
        void Shooting(cgf::Game* game);
        void GenerateShots(cgf::Game* game);
        void ControlShots(cgf::Game* game);

    private:
        std::vector<mm::LinearShoot*>* shoots;
};
}

#endif // SCREWDRIVER_H
