#ifndef ENEMY_H
#define ENEMY_H

#include <Entity.h>
#include "Game.h"
#include "PlayableCharacter.h"

namespace mm {
class Enemy : public Entity {
    public:
        Enemy(PlayableCharacter* player, Stage* stage);
        virtual ~Enemy();
        bool IsOnScreen(cgf::Game* game);

    protected:
        PlayableCharacter* player;
        Stage* stage;
        cgf::Game* game;

    private:
};
}

#endif // ENEMY_H
