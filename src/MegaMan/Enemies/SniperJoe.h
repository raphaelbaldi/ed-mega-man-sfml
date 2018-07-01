#ifndef SNIPERJOE_H
#define SNIPERJOE_H

#include <Enemy.h>

namespace mm {
class SniperJoe : public Enemy {
    public:
        SniperJoe(PlayableCharacter* player, Stage* stage);
        virtual ~SniperJoe();
        void Update(cgf::Game* game, bool updatePosition);

    protected:

    private:
};
}

#endif // SNIPERJOE_H
