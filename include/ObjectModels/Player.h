#ifndef PLAYER_H
#define PLAYER_H

#include "../Interfaces/IValidable.h"

namespace object_models
{
    class Player : public interfaces::IValidable
    {
        private:

        int _id;
        int _position;
        int _coins;

        public:

        int id() { return _id; }
        int position() { return _position; }
        void position(int position) { _position = position; }
        int coins() { return _coins; }

        void credit(int coins);
        void debit(int coins);

        bool is_valid();
    };
}
#endif // PLAYER_H