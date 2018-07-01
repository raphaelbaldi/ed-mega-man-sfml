#ifndef SCREWDRIVER_H
#define SCREWDRIVER_H

#include <Enemy.h>

namespace mm {
class ScrewDriver : public Enemy {
    public:
        ScrewDriver(PlayableCharacter* player, Stage* stage);
        virtual ~ScrewDriver();

    protected:

    private:
};
}

#endif // SCREWDRIVER_H
