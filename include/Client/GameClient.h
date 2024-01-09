// Author: Gianmaria Frigo

#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

#include <vector>

#include "../Interfaces/IPlayer.h"
#include "../Engine/GameContext.h"
#include "../ObjectModels/GameConfiguration.h"
#include "../DependencyInjection/ServiceProvider.h"

namespace client
{
    class GameClient
    {
        private:

        std::vector<interfaces::IPlayer*> _players;
        object_models::GameConfiguration _configuration;
        engine::GameContext* _context;
            
        void execute_inner(object_models::GameInfo info);

        public:
        
        GameClient();

        void execute(std::vector<interfaces::IPlayer*> _players);
        void execute(std::vector<interfaces::IPlayer*> _players, object_models::GameConfiguration);
    };
}

#endif // GAME_CLIENT_H