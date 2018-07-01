#ifndef ENEMY_H
#define ENEMY_H

#include <Entity.h>
#include "Game.h"
#include "PlayableCharacter.h"

namespace mm {
class Enemy : public Entity {
    public:
        Enemy(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition);
        virtual ~Enemy();
        bool IsOnScreen(cgf::Game* game);

    protected:
        PlayableCharacter* player;
        Stage* stage;

        unsigned int currentState;

    private:
};
}

#endif // ENEMY_H
