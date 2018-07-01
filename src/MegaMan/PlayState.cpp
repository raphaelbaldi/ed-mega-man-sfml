#include "Game.h"
#include "PlayState.h"
#include "InputManager.h"

PlayState PlayState::m_PlayState;

void PlayState::init()
{
    // TODO: create a configuration file per stage to make initialization easier
    mm::StageArea* bombman01 = new mm::StageArea("bombman_01");
    mm::StageArea* bombman02 = new mm::StageArea("bombman_02");
    mm::StageArea* bombman03 = new mm::StageArea("bombman_03");
    mm::StageArea* bombman04 = new mm::StageArea("bombman_04");
    mm::StageArea* bombman05 = new mm::StageArea("bombman_05");
    mm::StageArea* bombman06 = new mm::StageArea("bombman_06");
    mm::StageArea* bombman07_1 = new mm::StageArea("bombman_07_1");
    mm::StageArea* bombman07_2 = new mm::StageArea("bombman_07_2");
    mm::StageArea* bombman08 = new mm::StageArea("bombman_08");

    std::vector<mm::StageArea*>* areas = new std::vector<mm::StageArea*>();
    areas->push_back(bombman01);
    areas->push_back(bombman02);
    areas->push_back(bombman03);
    areas->push_back(bombman04);
    areas->push_back(bombman05);
    areas->push_back(bombman06);
    areas->push_back(bombman07_1);
    areas->push_back(bombman07_2);
    areas->push_back(bombman08);

    currentStage = new mm::Stage("content/level/bombman", areas, new sf::Color(57, 198, 255));

    entities = new std::vector<mm::Entity*>();
    mainCharacter = new mm::PlayableCharacter();
    mainCharacter->SetStage(currentStage);
    entities->push_back(mainCharacter);

    inputManager = cgf::InputManager::instance();
    inputManager->addKeyInput("left", sf::Keyboard::Left);
    inputManager->addKeyInput("right", sf::Keyboard::Right);
    inputManager->addKeyInput("up", sf::Keyboard::Up);
    inputManager->addKeyInput("down", sf::Keyboard::Down);
    inputManager->addKeyInput("jump", sf::Keyboard::Space);
    inputManager->addKeyInput("shoot", sf::Keyboard::A);
    inputManager->addKeyInput("start", sf::Keyboard::Return);
    inputManager->addKeyInput("select", sf::Keyboard::Home);
    inputManager->addKeyInput("quit", sf::Keyboard::Escape);
}

void PlayState::cleanup()
{
    delete currentStage;
    for(int i = 0; i < entities->size(); i++) {
        delete (*entities)[i];
    }
    delete entities;
}

void PlayState::pause()
{
}

void PlayState::resume()
{
}

void PlayState::handleEvents(cgf::Game* game)
{
    sf::View view = game->getScreen()->getView(); // gets the view
    sf::Event event;

    while (game->getScreen()->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            game->quit();
        }
    }

    for (int i = 0; i < entities->size(); i++) {
        if (nullptr != (*entities)[i]) {
            (*entities)[i]->HandleEvents(inputManager);
        }
    }

    if(inputManager->testEvent("quit")) {
        game->quit();
    }
}

void PlayState::update(cgf::Game* game)
{
    for (int i = 0; i < entities->size(); i++) {
        if (nullptr != (*entities)[i]) {
            (*entities)[i]->Update(game, true);
        }
    }
}

void PlayState::draw(cgf::Game* game)
{
    currentStage->CenterOnPosition(game->getScreen(), mainCharacter->GetPosition());
    currentStage->Render(game->getScreen());
    for (int i = 0; i < entities->size(); i++) {
        if (nullptr != (*entities)[i]) {
            (*entities)[i]->Render(game->getScreen());
        }
    }
}
