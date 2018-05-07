#ifndef PLAY_STATE_H_
#define PLAY_STATE_H_

#include <string>

#include "GameState.h"
#include "Sprite.h"
#include "InputManager.h"

#include "Map\Stage.h"
#include "Map\StageArea.h"

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
    static PlayState* instance()
    {
        return &m_PlayState;
    }

    protected:

    PlayState() {}

    private:

    static PlayState m_PlayState;

    enum { RIGHT=0, LEFT, UP, DOWN };
    std::string walkStates[4];
    int currentDir;

    int dirx, diry;

    cgf::Sprite player;
    cgf::Sprite enemy;

    sf::RenderWindow* screen;
    cgf::InputManager* im;

    mm::Stage* currentStage;

    // Centers the camera on the player position
    void centerMapOnPlayer();

    // Checks collision between a sprite and a map layer
    bool checkCollision(uint8_t layer, cgf::Game* game, cgf::Sprite* obj);

    // get a cell GID from the map (x and y in world coords)
    sf::Uint16 getCellFromMap(uint8_t layernum, float x, float y);
};

#endif
