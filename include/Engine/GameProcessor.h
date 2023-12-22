#ifndef GAME_PROCESSOR_H
#define GAME_PROCESSOR_H

#include "../ObjectModels/GameData.h"
#include "../ObjectModels/ActionInfo.h"

namespace engine
{
    class GameProcessor
    {
        private:

        public:

        GameProcessor() {}

        object_models::GameData process(object_models::GameData game, object_models::ActionInfo action);

    };
}

#endif // GAME_PROCESSOR_H