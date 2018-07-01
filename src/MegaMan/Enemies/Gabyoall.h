#ifndef GABYOALL_H
#define GABYOALL_H

#include <Enemy.h>

namespace mm {
    class Gabyoall : public Enemy {
        public:
            Gabyoall(PlayableCharacter* player, Stage* stage);
            virtual ~Gabyoall();

        protected:

        private:
    };
}

#endif // GABYOALL_H
