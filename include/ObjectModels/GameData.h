// Author: Gianmaria Frigo

#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "GameBoard.h"
#include "GameConfiguration.h"

namespace object_models
{
    class GameData
    {
        private:

        int _id;

        object_models::GameBoard _board;
        object_models::GameConfiguration _configuration;

        public:

        GameData() {}

        GameData(int id, object_models::GameConfiguration configuration);

        int id() { return _id; }

        object_models::GameBoard* board() { return &_board; }
        const object_models::GameConfiguration& configuration() const { return _configuration; }

        std::string board_to_string();
        std::string players_properties_to_string();
        std::string players_coins_to_string();

        std::string tile_to_string(Tile tile, int tile_index);
    };
}

#endif // GAME_DATA_H