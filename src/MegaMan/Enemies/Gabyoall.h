#ifndef GABYOALL_H
#define GABYOALL_H

#include <Enemy.h>

namespace mm {
class Gabyoall : public Enemy {
    public:
        Gabyoall(PlayableCharacter* player, Stage* stage);
        virtual ~Gabyoall();
        void Update(cgf::Game* game, bool updatePosition);

    protected:

    private:
};
}

#endif // GABYOALL_H
