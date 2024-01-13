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
    /// <summary>
    /// Data object that holds the information about a game board
    /// </summary>
    class GameBoard
    {
        private:
        
        int _roundCount;

        object_models::TurnManager _playerTurns;

        std::vector<object_models::PlayerData> _players;
        std::vector<object_models::Tile> _tiles;

        object_states::GameState _state;
        
        public:

        /// <summary>
        /// Default constructor
        /// </summary>
        GameBoard() {}

        /// <summary>
        /// Create a board with given tiles and players
        /// </summary>
        /// <param name="tiles">Tiles</param>
        /// <param name="players">Players</param>
        GameBoard(const std::vector<object_models::Tile>& tiles, const std::vector<object_models::PlayerData>& players);

        /// <summary>
        /// Get a reference to a specific tile from the board
        /// </summary>
        object_models::Tile& tile(int id) { return _tiles[id]; }
        
        /// <summary>
        /// Returns the size of the board
        /// </summary>
        /// <returns>The board size</returns>
        int board_size() { return _tiles.size(); }

        /// <summary>
        /// Returns the players turns
        /// </summary>
        object_models::TurnManager player_turns() { return _playerTurns; }
        
        /// <summary>
        /// Sets the players turns
        /// </summary>
        /// <param name="turns">Turns of the player</param>
        void player_turns(const std::vector<int>& turns) { _playerTurns = object_models::TurnManager(turns); }
        
        /// <summary>
        /// Gets current round
        /// </summary>
        /// <returns>Current round counter</returns>
        int round() { return _roundCount; }

        /// <summary>
        /// Sets the round to the next one
        /// </summary>
        void next_round()
        {
            _playerTurns.next_turn();
            _roundCount++;
        }

        /// <summary>
        /// Removes a player from the game
        /// </summary>
        /// <param name="player_index">The id of the player to be removed</param>
        void remove_player(int player_index) { _playerTurns.remove_player(player_index); }

        /// <summary>
        /// Get the player id of the winner
        /// </summary>
        /// <returns>Winner id</returns>
        int winner();

        /// <summary>
        /// Returns the player number
        /// </summary>
        int get_player_number() { return _players.size(); }

        /// <summary>
        /// Sets the players list
        /// </summary>
        /// <param name="players">The player lists</param>
        void players(const std::vector<PlayerData>& players) { _players = players; }
        
        /// <summary>
        /// Gets a pointer to the specified player
        /// </summary>
        /// <param name="i">The player id</param>
        object_models::PlayerData* player(int i) { return &_players[i]; } 

        /// <summary>
        /// Gets the state
        /// </summary>
        object_states::GameState state() { return _state; }

        /// <summary>
        /// Sets the state
        /// </summary>
        void state(object_states::GameState state) { _state = state; }
    };
}

#endif // GAME_BOARD_H