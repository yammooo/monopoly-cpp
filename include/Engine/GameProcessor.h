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

        object_models::GameInfo process(object_models::GameData* game, object_models::ActionInfo action);

        object_models::GameInfo init_game(object_models::GameData* game);
    };
}

#endif // GAME_PROCESSOR_H