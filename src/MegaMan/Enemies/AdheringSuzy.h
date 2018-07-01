#ifndef ADHERINGSUZY_H
#define ADHERINGSUZY_H

#include <Enemy.h>

namespace mm {
class AdheringSuzy : public Enemy {
    public:
        AdheringSuzy(PlayableCharacter* player, Stage* stage);
        virtual ~AdheringSuzy();

    protected:

    private:
};
}

#endif // ADHERINGSUZY_H
