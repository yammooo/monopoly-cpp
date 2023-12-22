#ifndef GAME_PROCESSOR_H
#define GAME_PROCESSOR_H

#include "RandomContext.h"
#include "../DependencyInjection/ServiceProvider.h"
#include "../ObjectModels/GameData.h"
#include "../ObjectModels/ActionInfo.h"
#include "../ObjectModels/GameInfo.h"

namespace engine
{
    class GameProcessor
    {
        private:

        engine::RandomContext* _random;

        public:

        GameProcessor();

        object_models::GameInfo process(object_models::GameData game, object_models::ActionInfo action);

    };
}

#endif // GAME_PROCESSOR_H