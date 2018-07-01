#ifndef BOMBOMBOMB_H
#define BOMBOMBOMB_H

#include <Enemy.h>

namespace mm {
class Bombombomb : public Enemy {
    public:
        Bombombomb(PlayableCharacter* player, Stage* stage);
        virtual ~Bombombomb();

    protected:

    private:
};
}

#endif // BOMBOMBOMB_H
