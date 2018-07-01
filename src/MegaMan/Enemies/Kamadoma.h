#ifndef KAMADOMA_H
#define KAMADOMA_H

#include <Enemy.h>

namespace mm {
    class Kamadoma : public Enemy {
        public:
            Kamadoma(PlayableCharacter* player, Stage* stage);
            virtual ~Kamadoma();

        protected:

        private:
    };
}

#endif // KAMADOMA_H
