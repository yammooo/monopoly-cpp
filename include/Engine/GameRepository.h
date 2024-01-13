// Author: Luca Bonaldo

#ifndef GAME_REPOSITORY_H
#define GAME_REPOSITORY_H

#include <map>
#include "../ObjectModels/GameData.h"
#include "../ObjectModels/PlayerData.h"

namespace engine
{
    /// <summary>
    /// Class that manage the game saved on memory
    /// </summary>
    class GameRepository
    {
        private:

        std::map<int, object_models::GameData> _games;

        public:

        /// <summary>
        /// Save a game into the repository memory
        /// </summary>
        /// <param name="game">The game to be saved</param>
        void save_game(object_models::GameData game);

        /// <summary>
        /// Get a game from the repository memory by its id
        /// </summary>
        /// <param name="id">The id of the game to retrieve</param>
        /// <returns>The retrieven game</returns>
        object_models::GameData get_game(int id);
    };
}

#endif // GAME_REPOSITORY_H