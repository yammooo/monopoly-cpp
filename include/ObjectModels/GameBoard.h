#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <vector>

#include "Tile.h"
#include "Player.h"
#include "../ObjectStates/GameState.h"

namespace object_models
{
    class GameBoard
    {
        private:
        
        int _roundCount;
        int _nextTurnPlayerIndex;

        std::vector<object_models::Player> _players;
        std::vector<object_models::Tile> _tiles;

        object_states::GameState _state;
        
        int _nextTurnPlayerId;

        public:

    };
}

#endif // GAME_BOARD_H