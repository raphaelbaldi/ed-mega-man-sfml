#ifndef ENEMY_H
#define ENEMY_H

#include <Entity.h>
#include "PlayableCharacter.h"

namespace mm {
class Enemy : public Entity {
    public:
        Enemy(PlayableCharacter* player, Stage* stage);
        virtual ~Enemy();

    protected:
        PlayableCharacter* player;
        Stage* stage;

    private:
};
}

#endif // ENEMY_H
