#include "Stage.h"

mm::Stage::Stage(std::string basePath, std::vector<mm::StageArea*>* areas, const sf::Color* stageColor)
{
    this->areas = areas;
    this->basePath = basePath;
    this->stageColor = stageColor;
    this->mapLoader = new tmx::MapLoader(basePath);
    this->currentArea = -1;
    this->SetArea(0);
}

void mm::Stage::SetArea(int newArea)
{
    if (newArea < 0 || newArea >= this->areas->size()) {
        return;
    }

    if (this->currentArea >= 0) {
        (*this->areas)[this->currentArea]->UnloadArea(this->mapLoader);
    }

    currentArea = newArea;
    (*this->areas)[this->currentArea]->LoadArea(this->mapLoader);
}

mm::Stage::~Stage()
{
}

void mm::Stage::Render(sf::RenderWindow* screen)
{
    screen->clear(*this->stageColor);

    if (this->currentArea >= 0 && this->currentArea < this->areas->size()) {
        this->mapLoader->Draw(*screen);
    }
}

void mm::Stage::CenterOnPosition(sf::RenderWindow* screen, sf::Vector2f position)
{
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

unsigned int mm::Stage::CheckCollision(uint8_t layer, cgf::Game* game, cgf::Sprite* object, bool ignoreVerticalMapBounds, bool ignoreHorizontalMapBounds)
{
    int i, x1, x2, y1, y2;
    unsigned int collision = 0;

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

    for (;;) {
        x1 = (px + vx) / tilesize.x;
        x2 = (px + vx + objsize.x - 1) / tilesize.x;

        y1 = (py) / tilesize.y;
        y2 = (py + i - 1) / tilesize.y;

        if (x1 >= 0 && x2 <= mapsize.x && y1 >= 0 && y2 <= mapsize.y) {
            if (vx > 0) {
                // Trying to move right
                int upRight   = GetCellFromMap(layer, x2 * tilesize.x, y1 * tilesize.y);
                int downRight = GetCellFromMap(layer, x2 * tilesize.x, y2 * tilesize.y);
                if (upRight || downRight) {
                    // Place the player as close to the solid tile as possible
                    px = x2 * tilesize.x;
                    px -= objsize.x;// + 1;
                    vx = 0;
                    collision |= RIGHT_COLLISION;
                }
            } else if (vx < 0) {
                // Trying to move left
                int upLeft   = GetCellFromMap(layer, x1 * tilesize.x, y1 * tilesize.y);
                int downLeft = GetCellFromMap(layer, x1 * tilesize.x, y2 * tilesize.y);
                if (upLeft || downLeft) {
                    // Place the player as close to the solid tile as possible
                    px = (x1+1) * tilesize.x;
                    vx = 0;
                    collision |= LEFT_COLLISION;
                }
            }
        }

        if (i == objsize.y) {
            break;
        }

        i += tilesize.y; // done, check next tile upwards

        if (i > objsize.y) {
            i = objsize.y;
        }
    }

    // Now test the vertical movement
    i = objsize.x > tilesize.x ? tilesize.x : objsize.x;

    for (;;) {
        x1 = (px / tilesize.x);
        x2 = ((px + i-1) / tilesize.x);

        y1 = ((py + vy) / tilesize.y);
        y2 = ((py + vy + objsize.y-1) / tilesize.y);

        if (x1 >= 0 && x2 <= mapsize.x && y1 >= 0 && y2 <= mapsize.y) {
            if (vy > 0) {
                // Trying to move down
                int downLeft  = GetCellFromMap(layer, x1 * tilesize.x, y2 * tilesize.y);
                int downRight = GetCellFromMap(layer, x2 * tilesize.x, y2 * tilesize.y);
                if (downLeft || downRight) {
                    // Place the player as close to the solid tile as possible
                    py = y2 * tilesize.y;
                    py -= objsize.y;
                    vy = 0;
                    collision |= DOWN_COLLISION;
                }
            } else if (vy < 0) {
                // Trying to move up
                int upLeft  = GetCellFromMap(layer, x1 * tilesize.x, y1 * tilesize.y);
                int upRight = GetCellFromMap(layer, x2 * tilesize.x, y1 * tilesize.y);
                if (upLeft || upRight) {
                    // Place the player as close to the solid tile as possible
                    py = (y1 + 1) * tilesize.y;
                    vy = 0;
                    collision |= UP_COLLISION;
                }
            }
        }

        if (i == objsize.x) {
            break;
        }

        i += tilesize.x; // done, check next tile to the right

        if (i > objsize.x) {
            i = objsize.x;
        }
    }

    // Check collision with edges of map
    if (px < 0) {
        collision |= LEFT_MAP_BOUND_COLLISION;
        if (!ignoreHorizontalMapBounds) {
            px = 0;
        }
    } else if (px + objsize.x >= mapsize.x * tilesize.x) {
        collision |= RIGHT_MAP_BOUND_COLLISION;
        if (!ignoreHorizontalMapBounds) {
            px = (mapsize.x * tilesize.x) - objsize.x;
        }
    }

    if(py < 0) {
        collision |= UP_MAP_BOUND_COLLISION;
        if (!ignoreVerticalMapBounds) {
            py = 0;
        }
    } else if(py + objsize.y >= mapsize.y * tilesize.y) {
        collision |= DOWN_MAP_BOUND_COLLISION;
        if (!ignoreVerticalMapBounds) {
            py = (mapsize.y * tilesize.y) - objsize.y;
        }
    }

    // Now apply the movement
    object->setPosition(px + vx, py + vy);
    px = object->getPosition().x;
    py = object->getPosition().y;

    return collision;
}

unsigned int mm::Stage::CheckSimpleCollision(uint8_t layer, cgf::Game* game, cgf::Sprite* object)
{
    unsigned int collision = 0;

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

    int minTileX = px / tilesize.x;
    int minTileY = py / tilesize.y;
    int maxTileX = (px + objsize.x) / tilesize.x;
    int maxTileY = (py + objsize.y) / tilesize.y;

    // Check horizontal collision
    for (int y = minTileY; y < maxTileY; ++y) {
        if (GetCellFromMap(layer, (float) minTileX * tilesize.x, (float) y * tilesize.y)) {
            px = (minTileX + 1) * tilesize.x + 1;
            collision |= LEFT_COLLISION;
            break;
        } else if (GetCellFromMap(layer, (float) maxTileX * tilesize.x, (float) y * tilesize.y)) {
            px = maxTileX * tilesize.x - objsize.x - 1;
            collision |= RIGHT_COLLISION;
            break;
        }
    }

    // Check vertical collision
    for (int x = minTileX; x < maxTileX; ++x) {
        if (GetCellFromMap(layer, x * tilesize.x, minTileY * tilesize.y)) {
            py = (minTileY + 1) * tilesize.y + 1;
            collision |= UP_COLLISION;
            break;
        } else if (GetCellFromMap(layer, x * tilesize.x, maxTileY * tilesize.y)) {
            py = maxTileY * tilesize.y - objsize.y - 1;
            collision |= DOWN_COLLISION;
            break;
        }
    }

    if (collision) {
        object->setPosition(px, py);
    }

    return collision;
}

sf::Uint16 mm::Stage::GetCellFromMap(uint8_t layerIndex, float px, float py)
{
    auto& layers = mapLoader->GetLayers();

    if (layerIndex < 0 || layerIndex >= layers.size()) {
        return 0;
    }

    tmx::MapLayer& layer = layers[layerIndex];
    sf::Vector2u mapsize = mapLoader->GetMapSize();
    sf::Vector2u tilesize = mapLoader->GetMapTileSize();
    mapsize.x /= tilesize.x;
    mapsize.y /= tilesize.y;
    int col = floor(px / tilesize.x);
    int row = floor(py / tilesize.y);
    int target = row*mapsize.x + col;

    if(target < 0 || target >= layer.tiles.size()) {
        return 0;
    }

    return layer.tiles[target].gid;
}

sf::Vector2f mm::Stage::GetRoundPosition(sf::Vector2f position)
{
    sf::Vector2u tilesize = mapLoader->GetMapTileSize();
    float x = floor(position.x / tilesize.x) * tilesize.x;
    float y = floor(position.y / tilesize.y) * tilesize.y;
    sf::Vector2f roundPos = sf::Vector2f(x, y);
    return roundPos;
}
