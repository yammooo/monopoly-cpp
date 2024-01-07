#ifndef GAME_RESULT_H
#define GAME_RESULT_H

#include <string>

#include "GameData.h"
#include "../Engine/GameLogger.h"
#include "../ObjectStates/GameState.h"

namespace object_models
{
    class GameInfo
    {
        private:

        int _id;
        int _round;

        object_states::GameState _state;

        int _playerNumber;
        object_models::TurnManager _playerTurns;
        int _winner;

        engine::GameLogger _logger;


        public:

        int id() const { return _id; }
        int player_number() const { return _playerNumber; }
        int round() const { return _round; }
        std::string log_to_string() const { return _logger.log_to_string(); }
        object_models::TurnManager player_turns() { return _playerTurns; }

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