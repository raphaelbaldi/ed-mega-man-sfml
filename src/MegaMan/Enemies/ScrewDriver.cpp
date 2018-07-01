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

    shoots = new std::vector<mm::LinearShoot*>();
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

    ControlShots(game);
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

        shotCounter = 0;
        shotTimer = idleTimer / (SHOTS_PER_SPAWN + 1);
    }
}

void mm::ScrewDriver::Shooting(cgf::Game* game)
{
    float dt = game->getUpdateInterval() / 1000;
    idleTimer -= dt;
    shotTimer -= dt;
    if (idleTimer <= 0) {
        if (sprite.isPlaying()) {
            sprite.pause();
        } else {
            idleTimer = IDLE_TIME;
            currentState = STATE_IDLE;
            sprite.setCurrentFrame(2);
        }
    } else if (shotTimer <= 0) {
        shotTimer = idleTimer / (SHOTS_PER_SPAWN + 1);
        if (shotCounter < SHOTS_PER_SPAWN) {
            ++shotCounter;
            GenerateShots(game);
        }
    }
}

void mm::ScrewDriver::GenerateShots(cgf::Game* game)
{
    // Generate 5 shots
    // TODO: use a for here
    sf::Vector2f spawnPosition;
    spawnPosition.x = sprite.getPosition().x + sprite.getSize().x * 0.38;
    spawnPosition.y = sprite.getPosition().y + 2;

    mm::LinearShoot* shot = new mm::LinearShoot(spawnPosition, sf::Vector2f(-SHOOT_SPEED, 0));
    shoots->push_back(shot);
    shot = new mm::LinearShoot(spawnPosition, sf::Vector2f(-SHOOT_SPEED * sin(45 * M_PI/180), -SHOOT_SPEED * sin(45 * M_PI/180)));
    shoots->push_back(shot);
    shot = new mm::LinearShoot(spawnPosition, sf::Vector2f(0, -SHOOT_SPEED));
    shoots->push_back(shot);
    shot = new mm::LinearShoot(spawnPosition, sf::Vector2f(SHOOT_SPEED * sin(45 * M_PI/180), -SHOOT_SPEED * sin(45 * M_PI/180)));
    shoots->push_back(shot);
    shot = new mm::LinearShoot(spawnPosition, sf::Vector2f(SHOOT_SPEED, 0));
    shoots->push_back(shot);
}

void mm::ScrewDriver::ControlShots(cgf::Game* game)
{
    int i, sSize = shoots->size();
    for(i = 0; i < sSize; ++i) {
        mm::LinearShoot* shoot = (*shoots)[i];
        if (nullptr == shoot || !shoot->IsOnScreen(game) || shoot->IsDestroyed()) {
            shoots->erase(shoots->begin() + i);
            --i;
            --sSize;
            if (nullptr != shoot) {
                delete(shoot);
            }
        } else {
            shoot->Update(game, true);
        }
    }
}

void mm::ScrewDriver::Render(sf::RenderWindow* screen)
{
    for(int i = 0; i < shoots->size(); ++i) {
        mm::LinearShoot* shoot = (*shoots)[i];
        if (nullptr != shoot) {
            shoot->Render(screen);
        }
    }
    Entity::Render(screen);
}
