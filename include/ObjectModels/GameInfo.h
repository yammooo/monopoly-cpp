// Author: Gianmaria Frigo

#ifndef GAME_RESULT_H
#define GAME_RESULT_H

#include <string>

#include "GameData.h"
#include "../Engine/GameLogger.h"
#include "../ObjectStates/GameState.h"

namespace object_models
{
    // The GameInfo class contains all the information about a game necessary for the client to play
    class GameInfo
    {
        private:

            int _id;
            int _round;

            object_states::GameState _state;

            int _playerNumber;
            object_models::TurnManager _playerTurns;
            int _winner;

            // A string representation of the game board
            std::string _board_string;

            // A string representation of the players' properties
            std::string _players_properties_string;

            // A string representation of all players' coins
            std::string _players_coins_string;

            engine::GameLogger _logger;

        public:

            int id() const { return _id; }
            int player_number() const { return _playerNumber; }
            int round() const { return _round; }
            std::string log_to_string() const { return _logger.log_to_string(); }
            object_models::TurnManager player_turns() { return _playerTurns; }

            std::string board_string() const { return _board_string; }
            std::string players_properties_string() const { return _players_properties_string; }
            std::string players_coins_string() const { return _players_coins_string; }

            int winner() const { return _winner; }

            object_states::GameState state() { return _state; }
            void state(object_states::GameState state) { _state = state; }

            GameInfo() {}
            GameInfo(int id);
            GameInfo(object_models::GameData game, engine::GameLogger logger);
            GameInfo(object_models::GameData game);
    };
}

#endif // GAME_RESULT_H