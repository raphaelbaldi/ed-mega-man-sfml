#include "Entity.h"

mm::Entity::Entity() {
}

mm::Entity::~Entity() {
}

void mm::Entity::Update(cgf::Game* game) {
    sprite.update(game->getUpdateInterval());
}

void mm::Entity::Render(sf::RenderWindow* screen) {
    sprite.setPosition(position);
    screen->draw(sprite);
}

sf::Vector2f mm::Entity::GetPosition() {
    return position;
}

void mm::Entity::HandleEvents(cgf::InputManager* inputManager) {
}
