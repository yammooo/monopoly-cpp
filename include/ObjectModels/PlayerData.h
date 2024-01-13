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

        /// <summary>
        /// Default constructor
        /// </summary>
        PlayerData() {}

        /// <summary>
        /// Constructor with id, position and coins
        /// </summary>
        PlayerData(int id, int position, int coins);

        /// <summary>
        /// Gets the player id
        /// </summary>
        int id() { return _id; }

        /// <summary>
        /// Gets the position on the board
        /// </summary>
        /// <returns>The position of the player</returns>
        int position() { return _position; }
        
        /// <summary>
        /// Sets position onm the board
        /// </summary>
        void position(int position) { _position = position; }
        
        /// <summary>
        /// Number of coins
        /// </summary>
        int coins() { return _coins; }

        /// <summary>
        /// Return true if the player is in game; false otherwise
        /// </summary>
        bool is_in_game() { return _coins >= 0; }

        /// <summary>
        /// Credits a certain amount of coins
        /// </summary>
        void credit(int coins);

        /// <summary>
        /// Debits a certain amount of coins
        /// </summary>
        void debit(int coins);

        /// <summary>
        /// Checks if the player is valid
        /// </summary>
        bool is_valid();
    };
}
#endif // PLAYER_H