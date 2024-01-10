// Author: Gianmaria Frigo

#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

#include <vector>
#include <memory>

#include "../Interfaces/IPlayer.h"
#include "../Engine/GameContext.h"
#include "../ObjectModels/GameConfiguration.h"
#include "../DependencyInjection/ServiceProvider.h"

namespace client
{
    class GameClient
    {
        private:

            std::vector<std::shared_ptr<interfaces::IPlayer>> _players;
            object_models::GameConfiguration _configuration;
            engine::GameContext* _context;
                
            void execute_inner(object_models::GameInfo info);

        public:
            
            GameClient();

            // Method to execute the game with a vector of players and the default configuration
            void execute(std::vector<std::shared_ptr<interfaces::IPlayer>> players);

            // Method to execute the game with a vector of players and a game configuration
            void execute(std::vector<std::shared_ptr<interfaces::IPlayer>> players, object_models::GameConfiguration);
    };
}

#endif // GAME_CLIENT_H