#ifndef GAME_RESULT_H
#define GAME_RESULT_H

#include "GameData.h"
#include "../Engine/GameLogger.h"

namespace object_models
{
    class GameInfo
    {
        private:

        int _id;
        int _round;

        object_states::GameState _state;

        int _playerNumber;
        std::vector<int> _playerTurns;
        int _winner;

        engine::GameLogger _logger;


        public:

        int id() { return _id; }
        int player_number() { return _playerNumber; }
        int round() { return _round; }
        std::vector<int> player_turns() { return _playerTurns; }

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