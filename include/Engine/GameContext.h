#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include "GameRepository.h"
#include "GameProcessor.h"
#include "../DependencyInjection/ServiceProvider.h"
#include "../ObjectModels/ActionInfo.h"

namespace engine
{
    class GameContext
    {
        private:

        int _nextId;

        engine::GameRepository _repository;
        engine::GameProcessor _processor;

        public:

        GameContext();

        int create_game();

        void play(int id, object_models::ActionInfo info);

    };
}

#endif // GAME_CONTEXT_H