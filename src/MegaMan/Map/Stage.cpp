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
