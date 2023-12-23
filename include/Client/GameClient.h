#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

#include "../Engine/GameContext.h"
#include "../DependencyInjection/ServiceProvider.h"

namespace client
{
    class GameClient
    {
        private:

        engine::GameContext* _context;

        public:
        
        GameClient();

        void execute();
    };
}

#endif // GAME_CLIENT_H