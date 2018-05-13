#include "StageArea.h"

mm::StageArea::StageArea(std::string areaName) {
    this->areaName = areaName;
}

mm::StageArea::~StageArea() {
}

void mm::StageArea::LoadArea(tmx::MapLoader* mapLoader)
{
    std::stringstream ss;
    ss << areaName << ".tmx";
    mapLoader->Load(ss.str());
}

void mm::StageArea::UnloadArea(tmx::MapLoader* mapLoader) {
}

void mm::StageArea::Render(sf::RenderWindow* screen) {
}
