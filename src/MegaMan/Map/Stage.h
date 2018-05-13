#ifndef STAGE_H
#define STAGE_H

#include <vector>
#include <string>
#include <tmx/MapLoader.h>

#include "Sprite.h"
#include "StageArea.h"
namespace mm
{
    class Stage
    {
        public:
            // Gets an ordered list of areas to explore
            Stage(std::string basePath, std::vector<mm::StageArea*>* areas, const sf::Color* stageColor);
            virtual ~Stage();
            virtual void SetArea(int newArea);
            virtual void Render(sf::RenderWindow* screen);
            void CenterOnPosition(sf::RenderWindow* screen, sf::Vector2f position);

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
