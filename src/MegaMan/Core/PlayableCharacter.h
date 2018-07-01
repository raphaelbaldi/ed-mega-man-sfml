#ifndef PLAYABLECHARACTER_H
#define PLAYABLECHARACTER_H

#include "Character.h"
#include "Stage.h"


namespace mm {
class PlayableCharacter : public Character {
    public:
        PlayableCharacter(sf::Vector2f startPosition);
        virtual ~PlayableCharacter();
        void HandleEvents(cgf::InputManager* inputManager);
        void SetStage(mm::Stage* stage);
        void Render(sf::RenderWindow* window);
        void Update(cgf::Game* game, bool updatePosition);

    protected:
        sf::Vector2f moveDirection;
        bool isClimbingStair;
        bool jumpPressed;
        mm::Stage* stage;
        void Animate();
        void Shoot();
        sf::RectangleShape* rectangle;

    private:
};
}

#endif // PLAYABLECHARACTER_H
