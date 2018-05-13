#ifndef PLAYABLECHARACTER_H
#define PLAYABLECHARACTER_H

#include "Character.h"
#include "Stage.h"


namespace mm
{
    class PlayableCharacter : public Character
    {
        public:
            PlayableCharacter();
            virtual ~PlayableCharacter();
            void HandleEvents(cgf::InputManager* inputManager);
            void SetStage(mm::Stage* stage);

        protected:
            bool isClimbingStair;
            mm::Stage* stage;
            void Animate();
            void Update(cgf::Game* game);
            void Shoot();
            bool IsGrounded();

        private:
    };
}

#endif // PLAYABLECHARACTER_H
