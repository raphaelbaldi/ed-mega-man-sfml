#ifndef PLAYABLECHARACTER_H
#define PLAYABLECHARACTER_H

#include "Character.h"


namespace mm
{
    class PlayableCharacter : public Character
    {
        public:
            PlayableCharacter();
            virtual ~PlayableCharacter();
            void HandleEvents(cgf::InputManager* inputManager);

        protected:

        private:
    };
}

#endif // PLAYABLECHARACTER_H
