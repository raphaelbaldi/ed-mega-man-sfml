#include "StageArea.h"

mm::StageArea::StageArea(std::string areaName)
{
    //ctor
    this->areaName = areaName;
}

mm::StageArea::~StageArea()
{
    //dtor
}

void mm::StageArea::LoadArea(tmx::MapLoader* mapLoader)
{
    std::stringstream ss;
    ss << areaName << ".tmx";
    mapLoader->Load(ss.str());
}

void mm::StageArea::UnloadArea(tmx::MapLoader* mapLoader)
{

}

void mm::StageArea::Render(sf::RenderWindow* screen)
{

}
