// Author: Luca Bonaldo

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

        /// <summary>
        /// Default constructor
        /// </summary>
        GameContext();

        /// <summary>
        /// Constructor with game context
        /// </summary>
        GameContext(const engine::GameContext&);
        
        /// <summary>
        /// Create a new game with default configuration
        /// </summary>
        /// <returns>The resulting game info</returns>
        object_models::Result<object_models::GameInfo> create_game();
        
        /// <summary>
        /// Create a new game with a specific configuration 
        /// </summary>
        /// <param name="configuration">The custom configuration</param>
        /// <returns>The resulting game info</returns>
        object_models::Result<object_models::GameInfo> create_game(object_models::GameConfiguration configuration);

        /// <summary>
        /// Perform an action on an existing game
        /// </summary>
        /// <param name="id">The game id on which the action should be performed</param>
        /// <param name="info">The action to perform</param>
        /// <returns>The resulting game info</returns>
        object_models::Result<object_models::GameInfo> play(int id, object_models::ActionInfo info);
    };
}

#endif // GAME_CONTEXT_H