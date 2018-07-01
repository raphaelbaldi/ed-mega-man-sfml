#ifndef KILLERBOMB_H
#define KILLERBOMB_H

#include <Enemy.h>

namespace mm {
class KillerBomb : public Enemy {
    public:
        KillerBomb(PlayableCharacter* player, Stage* stage);
        virtual ~KillerBomb();

    protected:

    private:
};
}

#endif // KILLERBOMB_H
