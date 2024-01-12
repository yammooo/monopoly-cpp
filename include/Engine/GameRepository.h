// Author: Luca Bonaldo

#ifndef GAME_REPOSITORY_H
#define GAME_REPOSITORY_H

#include <map>
#include "../ObjectModels/GameData.h"
#include "../ObjectModels/PlayerData.h"

namespace engine
{
    class GameRepository
    {
        private:

        std::map<int, object_models::GameData> _games;

        public:

        void save_game(object_models::GameData game);
        object_models::GameData get_game(int id);
    };
}

#endif // GAME_REPOSITORY_H