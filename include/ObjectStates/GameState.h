#ifndef GAME_STATE_H
#define GAME_STATE_H

namespace object_states
{
    enum class GameState
    {
        Undefined = 0,
        PlayerDiceThrow = 1,
        InProgress = 2,
        Ended = 3
    };
}

#endif // GAME_STATE_H