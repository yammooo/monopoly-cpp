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
    };
}

#endif // GAME_DATA_H