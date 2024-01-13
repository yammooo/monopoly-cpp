// Author: Gianmaria Frigo

#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "GameBoard.h"
#include "GameConfiguration.h"

namespace object_models
{
    // The GameData class contains all the data related to a single game session.
    // It includes the game board, game configuration, and the id for the game.
    class GameData
    {
        private:

        int _id;

        object_models::GameBoard _board;
        object_models::GameConfiguration _configuration;

        public:

        GameData() {}

        // Constructor that initializes the game with a specific ID and configuration
        GameData(int id, object_models::GameConfiguration configuration);

        int id() { return _id; }

        object_models::GameBoard* board() { return &_board; }
        const object_models::GameConfiguration& configuration() const { return _configuration; }

        // Outputs a string representation of the game board
        std::string board_to_string();

        // Outputs a string containing the players' properties
        std::string players_properties_to_string();

        // Outputs a string containing all the players' coins
        std::string players_coins_to_string();

        std::string tile_to_string(Tile tile, int tile_index);
    };
}

#endif // GAME_DATA_H