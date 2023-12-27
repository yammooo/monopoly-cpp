#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <vector>

#include "Tile.h"
#include "PlayerData.h"
#include "../ObjectStates/GameState.h"

namespace object_models
{
    class GameBoard
    {
        private:
        
        int _roundCount;

        std::vector<int> _playerTurns;

        std::vector<object_models::PlayerData> _players;
        std::vector<object_models::Tile> _tiles;

        object_states::GameState _state;
        
        public:

        GameBoard() {}

        GameBoard(const std::vector<object_models::Tile>& tiles, const std::vector<object_models::PlayerData>& players);

        object_models::Tile& tile(int id) { return _tiles[id]; }

        std::vector<int> player_turns() { return _playerTurns; }
        void player_turns(const std::vector<int>& turns) { _playerTurns = turns; }
        
        int round() { return _roundCount; }
        void next_round() { _roundCount++; }

        int winner();

        int get_player_number() { return _players.size(); }

        void players(const std::vector<PlayerData>& players) { _players = players; }
        object_models::PlayerData* player(int i) { return &_players[i]; } 

        object_states::GameState state() { return _state; }
        void state(object_states::GameState state) { _state = state; }

    };
}

#endif // GAME_BOARD_H