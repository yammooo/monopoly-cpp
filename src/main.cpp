#include <iostream>
#include <memory>
#include <typeinfo>

#include "../include/DependencyInjection/ServiceProvider.h"

#include "../include/Client/GameClient.h"

#include "../include/Engine/GameContext.h"
#include "../include/Engine/RandomContext.h"
#include "../include/Engine/GameProcessor.h"
#include "../include/Engine/GameRepository.h"

#include "../include/ObjectModels/GameBoard.h"
#include "../include/ObjectModels/Player.h"
#include "../include/ObjectModels/Tile.h"
#include "../include/ObjectModels/GameConfiguration.h"
#include "../include/ObjectModels/Result.h"

using namespace dependency_injection;
using namespace client;
using namespace engine;
using namespace object_models;

void build_services()
{
    ServiceProvider::register_service<GameRepository>();
    ServiceProvider::register_service<RandomContext>();
    ServiceProvider::register_service<GameProcessor>();
    ServiceProvider::register_service<GameContext>();
    ServiceProvider::register_service<GameClient>();
}

int main(int argc, char** argv)
{
    // Build services

    build_services();

    try
    {
        ServiceProvider::get_service<GameClient>()->execute();
        
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return -1;
}