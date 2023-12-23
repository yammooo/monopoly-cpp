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

        std::vector<int> _playerTurns;

        std::vector<object_models::Player> _players;
        std::vector<object_models::Tile> _tiles;

        object_states::GameState _state;
        
        public:

        void playerTurns(const std::vector<int>& turns) { _playerTurns = turns; }
        
        void players(const std::vector<Player>& players) { _players = players; }
        object_models::Player* player(int i) { return &_players[i]; } 


    };
}

#endif // GAME_BOARD_H