#include <iostream>
#include <cmath>
#include "Game.h"
#include "PlayState.h"
#include "InputManager.h"

PlayState PlayState::m_PlayState;

using namespace std;

void PlayState::init() {
    // TODO: create a configuration file per stage to make initialization easier
    mm::StageArea* bombman01 = new mm::StageArea("bombman_01");
    mm::StageArea* bombman02 = new mm::StageArea("bombman_02");
    mm::StageArea* bombman03 = new mm::StageArea("bombman_03");
    mm::StageArea* bombman04 = new mm::StageArea("bombman_04");
    mm::StageArea* bombman05 = new mm::StageArea("bombman_05");
    mm::StageArea* bombman06 = new mm::StageArea("bombman_06");
    mm::StageArea* bombman07_1 = new mm::StageArea("bombman_07_1");
    mm::StageArea* bombman07_2 = new mm::StageArea("bombman_07_2");
    mm::StageArea* bombman08 = new mm::StageArea("bombman_08");

    std::vector<mm::StageArea*>* areas = new std::vector<mm::StageArea*>();
    areas->push_back(bombman01);
    areas->push_back(bombman02);
    areas->push_back(bombman03);
    areas->push_back(bombman04);
    areas->push_back(bombman05);
    areas->push_back(bombman06);
    areas->push_back(bombman07_1);
    areas->push_back(bombman07_2);
    areas->push_back(bombman08);

    currentStage = new mm::Stage("content/level/bombman", areas, new sf::Color(57, 198, 255));

    im = cgf::InputManager::instance();

    im->addKeyInput("left", sf::Keyboard::Left);
    im->addKeyInput("right", sf::Keyboard::Right);
    im->addKeyInput("up", sf::Keyboard::Up);
    im->addKeyInput("down", sf::Keyboard::Down);
    im->addKeyInput("jump", sf::Keyboard::Space);
    im->addKeyInput("start", sf::Keyboard::Return);
    im->addKeyInput("select", sf::Keyboard::Home);
    im->addKeyInput("quit", sf::Keyboard::Escape);

    cout << "PlayState: Init" << endl;
}

void PlayState::cleanup() {
    delete currentStage;
    cout << "PlayState: Clean" << endl;
}

void PlayState::pause() {
    cout << "PlayState: Paused" << endl;
}

void PlayState::resume() {
    cout << "PlayState: Resumed" << endl;
}

void PlayState::handleEvents(cgf::Game* game) {
    screen = game->getScreen();
    sf::View view = screen->getView(); // gets the view
    sf::Event event;

    while (screen->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            game->quit();
        }
    }

    /*dirx = diry = 0;
    int newDir = currentDir;

    if(im->testEvent("left")) {
        dirx = -1;
        newDir = LEFT;
    }

    if(im->testEvent("right")) {
        dirx = 1;
        newDir = RIGHT;
    }

    if(im->testEvent("up")) {
        diry = -1;
        newDir = UP;
    }

    if(im->testEvent("down")) {
        diry = 1;
        newDir = DOWN;
    }*/

    if(im->testEvent("quit"))
        game->quit();

    if(im->testEvent("start")) {

    }
}

void PlayState::update(cgf::Game* game) {
}

void PlayState::draw(cgf::Game* game) {
    //currentStage->CenterOnPosition(game->getScreen(), mainCharacter->GetPosition());
    currentStage->Render(game->getScreen());
}

bool PlayState::checkCollision(uint8_t layer, cgf::Game* game, cgf::Sprite* obj) {
    /*
    int i, x1, x2, y1, y2;
    bool bump = false;

    // Get the limits of the map
    sf::Vector2u mapsize = map->GetMapSize();
    // Get the width and height of a single tile

    sf::Vector2u tilesize = map->GetMapTileSize();

    mapsize.x /= tilesize.x;
    mapsize.y /= tilesize.y;
    mapsize.x--;
    mapsize.y--;

    // Get the height and width of the object (in this case, 100% of a tile)
    sf::Vector2u objsize = obj->getSize();
    objsize.x *= obj->getScale().x;
    objsize.y *= obj->getScale().y;

    float px = obj->getPosition().x;
    float py = obj->getPosition().y;

    double deltaTime = game->getUpdateInterval();

    sf::Vector2f offset(obj->getXspeed()/1000 * deltaTime, obj->getYspeed()/1000 * deltaTime);

    float vx = offset.x;
    float vy = offset.y;

    // Test the horizontal movement first
    i = objsize.y > tilesize.y ? tilesize.y : objsize.y;

    for (;;)
    {
        x1 = (px + vx) / tilesize.x;
        x2 = (px + vx + objsize.x - 1) / tilesize.x;

        y1 = (py) / tilesize.y;
        y2 = (py + i - 1) / tilesize.y;

        if (x1 >= 0 && x2 < mapsize.x && y1 >= 0 && y2 < mapsize.y)
        {
            if (vx > 0)
            {
                // Trying to move right

                int upRight   = getCellFromMap(layer, x2*tilesize.x, y1*tilesize.y);
                int downRight = getCellFromMap(layer, x2*tilesize.x, y2*tilesize.y);
                if (upRight || downRight)
                {
                    // Place the player as close to the solid tile as possible
                    px = x2 * tilesize.x;
                    px -= objsize.x;// + 1;
                    vx = 0;
                    bump = true;
                }
            }

            else if (vx < 0)
            {
                // Trying to move left

                int upLeft   = getCellFromMap(layer, x1*tilesize.x, y1*tilesize.y);
                int downLeft = getCellFromMap(layer, x1*tilesize.x, y2*tilesize.y);
                if (upLeft || downLeft)
                {
                    // Place the player as close to the solid tile as possible
                    px = (x1+1) * tilesize.x;
                    vx = 0;
                    bump = true;
                }
            }
        }

        if (i == objsize.y) // Checked player height with all tiles ?
        {
            break;
        }

        i += tilesize.y; // done, check next tile upwards

        if (i > objsize.y)
        {
            i = objsize.y;
        }
    }

    // Now test the vertical movement
    i = objsize.x > tilesize.x ? tilesize.x : objsize.x;

    for (;;)
    {
        x1 = (px / tilesize.x);
        x2 = ((px + i-1) / tilesize.x);

        y1 = ((py + vy) / tilesize.y);
        y2 = ((py + vy + objsize.y-1) / tilesize.y);

        if (x1 >= 0 && x2 < mapsize.x && y1 >= 0 && y2 < mapsize.y)
        {
            if (vy > 0)
            {
                // Trying to move down
                int downLeft  = getCellFromMap(layer, x1*tilesize.x, y2*tilesize.y);
                int downRight = getCellFromMap(layer, x2*tilesize.x, y2*tilesize.y);
                if (downLeft || downRight)
                {
                    // Place the player as close to the solid tile as possible
                    py = y2 * tilesize.y;
                    py -= objsize.y;
                    vy = 0;
                    bump = true;
                }
            }

            else if (vy < 0)
            {
                // Trying to move up

                int upLeft  = getCellFromMap(layer, x1*tilesize.x, y1*tilesize.y);
                int upRight = getCellFromMap(layer, x2*tilesize.x, y1*tilesize.y);
                if (upLeft || upRight)
                {
                    // Place the player as close to the solid tile as possible
                    py = (y1 + 1) * tilesize.y;
                    vy = 0;
                    bump = true;
                }
            }
        }

        if (i == objsize.x)
        {
            break;
        }

        i += tilesize.x; // done, check next tile to the right

        if (i > objsize.x)
        {
            i = objsize.x;
        }
    }

    // Now apply the movement and animation

    obj->setPosition(px+vx,py+vy);
    px = obj->getPosition().x;
    py = obj->getPosition().y;

    obj->update(deltaTime, false); // only update animation

    // Check collision with edges of map
    if (px < 0)
        obj->setPosition(px,py);
    else if (px + objsize.x >= mapsize.x * tilesize.x)
        obj->setPosition(mapsize.x*tilesize.x - objsize.x - 1,py);

    if(py < 0)
        obj->setPosition(px,0);
    else if(py + objsize.y >= mapsize.y * tilesize.y)
        obj->setPosition(px, mapsize.y*tilesize.y - objsize.y - 1);

    return bump;
    */
    return false;
}

// Get a cell GID from the map (x and y in global coords)
sf::Uint16 PlayState::getCellFromMap(uint8_t layernum, float x, float y) {
    /*
    auto& layers = map->GetLayers();
    tmx::MapLayer& layer = layers[layernum];
    sf::Vector2u mapsize = map->GetMapSize();
    sf::Vector2u tilesize = map->GetMapTileSize();
    mapsize.x /= tilesize.x;
    mapsize.y /= tilesize.y;
    int col = floor(x / tilesize.x);
    int row = floor(y / tilesize.y);
    return layer.tiles[row*mapsize.x + col].gid;
    */
}
