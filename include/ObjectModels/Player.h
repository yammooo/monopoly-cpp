#ifndef PLAYER_H
#define PLAYER_H

#include "../Interfaces/IValidable.h"

namespace object_models
{
    class Player : public interfaces::IValidable
    {
        private:

        int _id;
        int _boardPosition;

        public:

        bool is_valid();
    };
}
#endif // PLAYER_H