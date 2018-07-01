#ifndef BOMBOMBOMB_H
#define BOMBOMBOMB_H

#include <Enemy.h>

namespace mm {
class Bombombomb : public Enemy {
    public:
        Bombombomb(PlayableCharacter* player, Stage* stage);
        virtual ~Bombombomb();
        void Update(cgf::Game* game, bool updatePosition);

    protected:
        const static unsigned int STATE_GOING_UP = 1;
        const static unsigned int EXPLODED = 2;

        const float MAX_DELTA_HEIGTH = 120; // Delta height, from start to explosion point

        void UpdatePosition(cgf::Game* game);
        void UpdateShoots(cgf::Game* game);


    private:
};
}

#endif // BOMBOMBOMB_H
