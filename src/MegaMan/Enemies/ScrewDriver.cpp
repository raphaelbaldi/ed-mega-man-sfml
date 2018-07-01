#include "ScrewDriver.h"

mm::ScrewDriver::ScrewDriver(PlayableCharacter* player, Stage* stage, sf::Vector2f startPosition)
    : Enemy(player, stage, startPosition)
{
    sprite.load("content/enemies/screw-driver.png", 16, 16, 0, 0, 0, 0, 4, 1);

    sprite.setFrameRange(0, 2);
    sprite.setLooped(true);
    sprite.setAnimRate(ANIMATION_SPEED);
    sprite.pause();

    idleTimer = IDLE_TIME;

    currentState = STATE_IDLE;
}

mm::ScrewDriver::~ScrewDriver()
{
    //dtor
}

void mm::ScrewDriver::Update(cgf::Game* game, bool updatePosition)
{
    switch(currentState) {
    case STATE_IDLE:
        Idle(game);
        break;
    case STATE_SHOOTING:
        Shooting(game);
        break;
    }

    ControlShoots(game);
    Entity::Update(game, false);
}

void mm::ScrewDriver::Idle(cgf::Game* game)
{
    sprite.setCurrentFrame(3);
    idleTimer -= game->getUpdateInterval() / 1000;
    if (idleTimer <= 0) {
        idleTimer = SHOOT_TIME;
        currentState = STATE_SHOOTING;
        sprite.play();

        shootCounter = 0;
        shootTimer = idleTimer / (SHOOTS_PER_SPAWN + 1);
    }
}

void mm::ScrewDriver::Shooting(cgf::Game* game)
{
    float dt = game->getUpdateInterval() / 1000;
    idleTimer -= dt;
    shootTimer -= dt;
    if (idleTimer <= 0) {
        if (sprite.isPlaying()) {
            sprite.pause();
        } else {
            idleTimer = IDLE_TIME;
            currentState = STATE_IDLE;
            sprite.setCurrentFrame(2);
        }
    } else if (shootTimer <= 0) {
        shootTimer = idleTimer / (SHOOTS_PER_SPAWN + 1);
        if (shootCounter < SHOOTS_PER_SPAWN) {
            ++shootCounter;
            GenerateShoots(game);
        }
    }
}

void mm::ScrewDriver::GenerateShoots(cgf::Game* game)
{
}

void mm::ScrewDriver::ControlShoots(cgf::Game* game)
{
}
