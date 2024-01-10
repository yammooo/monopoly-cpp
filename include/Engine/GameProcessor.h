// Author: Gianmaria Frigo

#ifndef GAME_PROCESSOR_H
#define GAME_PROCESSOR_H

#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>

#include "RandomContext.h"
#include "../DependencyInjection/ServiceProvider.h"
#include "../ObjectModels/GameData.h"
#include "../ObjectModels/ActionInfo.h"
#include "../ObjectStates/GameState.h"
#include "../ObjectModels/GameInfo.h"
#include "../ObjectModels/PlayerData.h"

namespace engine
{
    class GameProcessor
    {
        private:

            engine::RandomContext* _random;

        public:

            GameProcessor();

            // This method takes the current game data and a player action,
            // processes the action, and returns the updated game data.
            object_models::GameInfo process(object_models::GameData* game, object_models::ActionInfo action);

            // This function initializes the game by throwing the dices for each player,
            // setting the player turns and initializing player data objects in the GameBoard.
            object_models::GameInfo init_game(object_models::GameData* game);
    };
}

#endif // GAME_PROCESSOR_H