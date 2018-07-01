#include "Enemy.h"

mm::Enemy::Enemy(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition)
    : Entity(startPosition)
{
    //ctor
    this->player = player;
    this->stage = stage;
}

mm::Enemy::~Enemy()
{
    //dtor
}

bool mm::Enemy::IsOnScreen(cgf::Game* game)
{
    if (nullptr == game) {
        return true;
    }

    sf::View view = game->getScreen()->getView();

    sf::Vector2u spriteSize = sprite.getSize();
    spriteSize.x *= sprite.getScale().x;
    spriteSize.y *= sprite.getScale().y;

    float viewWSize = view.getSize().x / 2;
    float viewVSize = view.getSize().y / 2;
    if (sprite.getPosition().x + spriteSize.x < view.getCenter().x - viewWSize ||
        sprite.getPosition().x > view.getCenter().x + viewWSize ||
        sprite.getPosition().y + spriteSize.y < view.getCenter().y - viewVSize ||
        sprite.getPosition().y > view.getCenter().y + viewVSize) {
            return false;
    }

    return true;
}
