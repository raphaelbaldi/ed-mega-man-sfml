#ifndef STAGEAREA_H
#define STAGEAREA_H

#include <string>
#include <sstream>

#include <tmx/MapLoader.h>

namespace mm {
class StageArea {
    public:
        StageArea(std::string areaName);
        virtual ~StageArea();
        virtual void LoadArea(tmx::MapLoader* mapLoader);
        virtual void UnloadArea(tmx::MapLoader* mapLoader);
        virtual void Render(sf::RenderWindow* screen);

    protected:
        std::string areaName;

    private:
};
}
#endif // STAGEAREA_H
