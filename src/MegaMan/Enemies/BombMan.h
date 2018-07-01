#ifndef BOMBMAN_H
#define BOMBMAN_H

#include <Enemy.h>

namespace mm {
class BombMan : public Enemy {
    public:
        BombMan(PlayableCharacter* player, Stage* stage);
        virtual ~BombMan();

    protected:

    private:
};
}

#endif // BOMBMAN_H
