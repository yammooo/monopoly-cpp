// Author: Luca Bonaldo

#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <string>

#include "Tile.h"
#include "PlayerData.h"
#include "TurnManager.h"
#include "../ObjectStates/GameState.h"

namespace object_models
{
    class GameBoard
    {
        private:
        
        int _roundCount;

        object_models::TurnManager _playerTurns;

        std::vector<object_models::PlayerData> _players;
        std::vector<object_models::Tile> _tiles;

        object_states::GameState _state;
        
        public:

        GameBoard() {}

        GameBoard(const std::vector<object_models::Tile>& tiles, const std::vector<object_models::PlayerData>& players);

        object_models::Tile& tile(int id) { return _tiles[id]; }
        int get_tile_number() { return _tiles.size(); }

        object_models::TurnManager player_turns() { return _playerTurns; }
        void player_turns(const std::vector<int>& turns) { _playerTurns = object_models::TurnManager(turns); }
        
        int round() { return _roundCount; }

        void next_round()
        {
            _playerTurns.next_turn();
            _roundCount++;
        }

        void remove_player(int player_index) { _playerTurns.remove_player(player_index); }

        int winner();

        int get_player_number() { return _players.size(); }

        void players(const std::vector<PlayerData>& players) { _players = players; }
        object_models::PlayerData* player(int i) { return &_players[i]; } 

        object_states::GameState state() { return _state; }
        void state(object_states::GameState state) { _state = state; }
    };
}

#endif // GAME_BOARD_H