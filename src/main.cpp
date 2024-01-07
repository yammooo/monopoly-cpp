#include <iostream>
#include <memory>
#include <typeinfo>

#include "../include/DependencyInjection/ServiceProvider.h"

#include "../include/Client/GameClient.h"
#include "../include/Client/Bot.h"
#include "../include/Client/Player.h"

#include "../include/Interfaces/IPlayer.h"

#include "../include/Engine/GameLogger.h"
#include "../include/Engine/GameContext.h"
#include "../include/Engine/RandomContext.h"
#include "../include/Engine/GameProcessor.h"
#include "../include/Engine/GameRepository.h"

#include "../include/ObjectModels/GameBoard.h"
#include "../include/ObjectModels/PlayerData.h"
#include "../include/ObjectModels/Tile.h"
#include "../include/ObjectModels/GameConfiguration.h"
#include "../include/ObjectModels/Result.h"

using namespace dependency_injection;
using namespace client;
using namespace engine;
using namespace object_models;
using namespace interfaces;

void build_services()
{
    ServiceProvider::register_service<GameRepository>();
    ServiceProvider::register_service<RandomContext>();
    ServiceProvider::register_service<GameProcessor>();
    ServiceProvider::register_service<GameContext>();
    ServiceProvider::register_service<GameClient>();
    ServiceProvider::register_service<GameLogger>(std::vector<std::ostream*> {&(std::cout)});
}

int main(int argc, char** argv)
{
    // Build services

    build_services();

    std::vector<IPlayer*> players;

    /*if (argc != 2)
    {
        std::cout << "The arguments provided were wrong. The program must be called with 'human' or 'computer' as argument." << std::endl;
        return -1;
    }*/

    // Assume configuration is default

    players.push_back(new Player());
    players.push_back(new Player());    players.push_back(new Bot());
    players.push_back(new Bot());

    //if ("computer" == "computer")
    //{
    //    players.push_back(new Bot());
    //    players.push_back(new Bot());
    //    players.push_back(new Bot());
    //    players.push_back(new Bot());
    //}
    //else
    //{
    //    players.push_back(new Player());
    //    players.push_back(new Bot());
    //    players.push_back(new Bot());
    //    players.push_back(new Bot());
    //}
    
    try
    {
        ServiceProvider::get_service<GameClient>()->execute(players);
        
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return -1;
}