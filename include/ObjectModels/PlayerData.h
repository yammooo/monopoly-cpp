// Author: Luca Bonaldo

#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include "../Interfaces/IValidable.h"

namespace object_models
{
    class PlayerData : public interfaces::IValidable
    {
        private:

        int _id;
        int _position;
        int _coins;

        public:

        PlayerData() {}

        PlayerData(int id, int position, int coins);

        int id() { return _id; }
        int position() { return _position; }
        void position(int position) { _position = position; }
        int coins() { return _coins; }

        bool is_in_game() { return _coins >= 0; }

        void credit(int coins);
        void debit(int coins);

        bool is_valid();
    };
}
#endif // PLAYER_H