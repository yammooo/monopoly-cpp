#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include "GameRepository.h"
#include "GameProcessor.h"
#include "../DependencyInjection/ServiceProvider.h"
#include "../ObjectModels/ActionInfo.h"
#include "../ObjectModels/Result.h"

namespace engine
{
    class GameContext
    {
        private:

        int _nextId;

        engine::GameRepository* _repository;
        engine::GameProcessor* _processor;

        public:

        int value;

        GameContext();
        GameContext(const engine::GameContext&);
        
        object_models::Result<object_models::GameInfo> create_game();

        object_models::Result<object_models::GameInfo> play(int id, object_models::ActionInfo info);
    };
}

#endif // GAME_CONTEXT_H