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

    float panX = viewsize.x; // minimum pan
    if(position.x >= viewsize.x)
        panX = position.x;

    if(panX >= mapsize.x - viewsize.x)
        panX = mapsize.x - viewsize.x;

    float panY = viewsize.y; // minimum pan
    if(position.y >= viewsize.y)
        panY = position.y;

    if(panY >= mapsize.y - viewsize.y)
        panY = mapsize.y - viewsize.y;

    sf::Vector2f center(panX,panY);
    view.setCenter(center);
    screen->setView(view);
}
