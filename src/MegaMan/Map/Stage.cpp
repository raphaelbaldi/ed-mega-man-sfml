#include "Stage.h"

mm::Stage::Stage(std::string basePath, std::vector<mm::StageArea*>* areas, const sf::Color* stageColor)
{
    //ctor
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
    //dtor
}

void mm::Stage::Render(sf::RenderWindow* screen)
{
    screen->clear(*this->stageColor);

    if (this->currentArea >= 0 && this->currentArea < this->areas->size()) {
        //(*this->areas)[this->currentArea]->Render(screen);
        this->mapLoader->Draw(*screen);
    }
}
