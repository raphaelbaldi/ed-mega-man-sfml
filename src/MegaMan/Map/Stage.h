#ifndef STAGE_H
#define STAGE_H

#include <vector>
#include <string>
#include <tmx/MapLoader.h>

#include "Game.h"
#include "Sprite.h"
#include "StageArea.h"

#define COLLISION_LAYER 2

namespace mm {
class Stage {
    public:
        static const unsigned int LEFT_COLLISION = 1;
        static const unsigned int RIGHT_COLLISION = 2;
        static const unsigned int UP_COLLISION = 4;
        static const unsigned int DOWN_COLLISION = 8;
        static const unsigned int LEFT_MAP_BOUND_COLLISION = 16;
        static const unsigned int RIGHT_MAP_BOUND_COLLISION = 32;
        static const unsigned int UP_MAP_BOUND_COLLISION = 64;
        static const unsigned int DOWN_MAP_BOUND_COLLISION = 128;

        // Gets an ordered list of areas to explore
        Stage(std::string basePath, std::vector<mm::StageArea*>* areas, const sf::Color* stageColor);
        virtual ~Stage();
        virtual void SetArea(int newArea);
        virtual void Render(sf::RenderWindow* screen);
        void CenterOnPosition(sf::RenderWindow* screen, sf::Vector2f position);
        sf::Uint16 GetCellFromMap(uint8_t layer, float px, float py);
        unsigned int CheckCollision(uint8_t layer, cgf::Game* game, cgf::Sprite* object, bool ignoreVerticalMapBounds, bool ignoreHorizontalMapBounds);
        unsigned int CheckSimpleCollision(uint8_t layer, cgf::Game* game, cgf::Sprite* object);
        sf::Vector2f GetRoundPosition(sf::Vector2f position);

    protected:
        std::vector<mm::StageArea*>* areas;
        int currentArea;
        std::string basePath;
        const sf::Color* stageColor;
        tmx::MapLoader* mapLoader;

    private:
};
}
#endif // STAGE_H
