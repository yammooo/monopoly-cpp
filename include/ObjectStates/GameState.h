// Author: Luca Bonaldo

#ifndef GAME_STATE_H
#define GAME_STATE_H

namespace object_states
{
    /// <summary>
    /// States of the game
    /// </summary>
    enum class GameState
    {
        /// <summary>
        /// Undefined
        /// </summary>
        Undefined = 0,

        /// <summary>
        /// When a player need to throw dices
        /// </summary>
        PlayerDiceThrow = 1,

        /// <summary>
        /// Player can buy something
        /// </summary>
        PlayerBuyLand = 2,
        PlayerBuyHouse = 3,
        PlayerBuyHotel = 4,

        /// <summary>
        /// The game has ended
        /// </summary>
        Ended = 5
    };
}

#endif // GAME_STATE_H