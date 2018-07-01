#ifndef MAMBU_H
#define MAMBU_H

#include <Enemy.h>

namespace mm {
class Mambu : public Enemy {
    public:
        Mambu(PlayableCharacter* player, Stage* stage);
        virtual ~Mambu();

    protected:

    private:
};
}

#endif // MAMBU_H
