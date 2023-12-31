// Author: Luca Bonaldo

#ifndef GAME_STATE_H
#define GAME_STATE_H

namespace object_states
{
    enum class GameState
    {
        Undefined = 0,
        PlayerDiceThrow = 1,
        PlayerBuyLand = 2,
        PlayerBuyHouse = 3,
        PlayerBuyHotel = 4,
        Ended = 5
    };
}

#endif // GAME_STATE_H