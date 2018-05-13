#include "Stage.h"

mm::Stage::Stage(std::string basePath, std::vector<mm::StageArea*>* areas, const sf::Color* stageColor) {
    this->areas = areas;
    this->basePath = basePath;
    this->stageColor = stageColor;
    this->mapLoader = new tmx::MapLoader(basePath);
    this->currentArea = -1;
    this->SetArea(0);
}

void mm::Stage::SetArea(int newArea) {
    if (newArea < 0 || newArea >= this->areas->size()) {
        return;
    }

    if (this->currentArea >= 0) {
        (*this->areas)[this->currentArea]->UnloadArea(this->mapLoader);
    }

    currentArea = newArea;
    (*this->areas)[this->currentArea]->LoadArea(this->mapLoader);
}

mm::Stage::~Stage() {
}

void mm::Stage::Render(sf::RenderWindow* screen) {
    screen->clear(*this->stageColor);

    if (this->currentArea >= 0 && this->currentArea < this->areas->size()) {
        this->mapLoader->Draw(*screen);
    }
}

void mm::Stage::CenterOnPosition(sf::RenderWindow* screen, sf::Vector2f position) {
    sf::View view = screen->getView();
    sf::Vector2u mapsize = this->mapLoader->GetMapSize();
    sf::Vector2f viewsize = view.getSize();
    viewsize.x /= 2;
    viewsize.y /= 2;

    float panX = viewsize.x;
    if(position.x >= viewsize.x) {
        panX = position.x;
    }

    if(panX >= mapsize.x - viewsize.x) {
        panX = mapsize.x - viewsize.x;
    }

    float panY = viewsize.y;
    if(position.y >= viewsize.y) {
        panY = position.y;
    }

    if(panY >= mapsize.y - viewsize.y) {
        panY = mapsize.y - viewsize.y;
    }

    sf::Vector2f center(panX,panY);
    view.setCenter(center);
    screen->setView(view);
}

bool mm::Stage::CheckCollision(uint8_t layer, cgf::Game* game, cgf::Sprite* object) {
    int i, x1, x2, y1, y2;
    bool bump = false;

    // Get the limits of the map
    sf::Vector2u mapsize = mapLoader->GetMapSize();
    // Get the width and height of a single tile

    sf::Vector2u tilesize = mapLoader->GetMapTileSize();

    mapsize.x /= tilesize.x;
    mapsize.y /= tilesize.y;
    mapsize.x--;
    mapsize.y--;

    // Get the height and width of the object (in this case, 100% of a tile)
    sf::Vector2u objsize = object->getSize();
    objsize.x *= object->getScale().x;
    objsize.y *= object->getScale().y;

    float px = object->getPosition().x;
    float py = object->getPosition().y;

    double deltaTime = game->getUpdateInterval();

    sf::Vector2f offset(object->getXspeed()/1000 * deltaTime, object->getYspeed()/1000 * deltaTime);

    float vx = offset.x;
    float vy = offset.y;

    // Test the horizontal movement first
    i = objsize.y > tilesize.y ? tilesize.y : objsize.y;

    sf::Vector2f tempPosition;

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

                tempPosition.x = x2*tilesize.x;
                tempPosition.y = y1*tilesize.y;
                int upRight   = GetCellFromMap(layer, tempPosition);

                tempPosition.y = y2*tilesize.y;
                int downRight = GetCellFromMap(layer, tempPosition);
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

                tempPosition.x = x1*tilesize.x;
                tempPosition.y = y1*tilesize.y;
                int upLeft   = GetCellFromMap(layer, tempPosition);

                tempPosition.y = y2*tilesize.y;
                int downLeft = GetCellFromMap(layer, tempPosition);
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

                tempPosition.y = y2*tilesize.y;
                tempPosition.x = x1*tilesize.x;
                int downLeft  = GetCellFromMap(layer, tempPosition);

                tempPosition.x = x2*tilesize.x;
                int downRight = GetCellFromMap(layer, tempPosition);
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

                tempPosition.y = y1*tilesize.y;
                tempPosition.x = x1*tilesize.x;
                int upLeft  = GetCellFromMap(layer, tempPosition);

                tempPosition.x = x2*tilesize.x;
                int upRight = GetCellFromMap(layer, tempPosition);
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

    // Check collision with edges of map
    if (px < 0) {
        px = 0;
        bump = true;
    } else if (px + objsize.x >= mapsize.x * tilesize.x) {
        px = mapsize.x*tilesize.x - objsize.x - 1;
        bump = true;
    }

    if(py < 0) {
        py = 0;
        bump = true;
    } else if(py + objsize.y >= mapsize.y * tilesize.y) {
        py = mapsize.y*tilesize.y - objsize.y - 1;
        bump = true;
    }

    if(bump) {
        // Now apply the movement and animation
        object->setPosition(px,py);
    }

    return bump;
}


sf::Uint16 mm::Stage::GetCellFromMap(uint8_t layerIndex, sf::Vector2f position) {
    auto& layers = mapLoader->GetLayers();
    tmx::MapLayer& layer = layers[layerIndex];
    sf::Vector2u mapsize = mapLoader->GetMapSize();
    sf::Vector2u tilesize = mapLoader->GetMapTileSize();
    mapsize.x /= tilesize.x;
    mapsize.y /= tilesize.y;
    int col = floor(position.x / tilesize.x);
    int row = floor(position.y / tilesize.y);
    int target = row*mapsize.x + col;

    if(target < 0 || target >= layer.tiles.size()) {
        return 0;
    }

    return layer.tiles[target].gid;
}
