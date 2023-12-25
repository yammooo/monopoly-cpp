#ifndef GAME_STATE_H
#define GAME_STATE_H

namespace object_states
{
    enum class GameState
    {
        Undefined = 0,
        PlayerDiceThrow = 1,
        PlayerPayment = 2,
        InProgress = 3,
        Ended = 4
    };
}

#endif // GAME_STATE_H