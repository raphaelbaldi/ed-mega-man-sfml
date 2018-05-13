#ifndef PLAY_STATE_H_
#define PLAY_STATE_H_

#include <string>

#include "GameState.h"
#include "Sprite.h"
#include "InputManager.h"

#include "Map/Stage.h"
#include "Map/StageArea.h"
#include "Core/Entity.h"
#include "Core/PlayableCharacter.h"

class PlayState : public cgf::GameState
{
    public:
        void init();
        void cleanup();
        void pause();
        void resume();
        void handleEvents(cgf::Game* game);
        void update(cgf::Game* game);
        void draw(cgf::Game* game);

        // Implement Singleton Pattern
        static PlayState* instance() {
            return &m_PlayState;
        }

    protected:
        PlayState() {}

    private:
        static PlayState m_PlayState;

        cgf::InputManager* inputManager;
        mm::Stage* currentStage;
        mm::PlayableCharacter* mainCharacter;
        std::vector<mm::Entity*>* entities;
};

#endif
