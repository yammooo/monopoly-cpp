#include <iostream>
#include <memory>
#include <typeinfo>

#include "../include/Engine/GameContext.h"
#include "../include/ObjectModels/GameBoard.h"
#include "../include/ObjectModels/Player.h"
#include "../include/ObjectModels/Tile.h"
#include "../include/ObjectModels/GameConfiguration.h"
#include "../include/DependencyInjection/ServiceProvider.h"

#include "../include/Engine/RandomContext.h"
#include "../include/Engine/GameProcessor.h"
#include "../include/Engine/GameRepository.h"

#include "../include/ObjectModels/Result.h"

using namespace dependency_injection;
using namespace object_models;
using namespace engine;

void build_services()
{
    ServiceProvider::register_service<GameRepository>();
    ServiceProvider::register_service<RandomContext>();
    ServiceProvider::register_service<GameProcessor>();
    ServiceProvider::register_service<GameContext>();
}

int main(int argc, char** argv)
{
    // Build services

    build_services();

    auto context = ServiceProvider::get_service<GameContext>();

    auto game_result = context.create_game();

    if (!game_result.isError())
    {
        std::cout << "Success from success!" << std::endl;
    }

    if (game_result.isError())
    {
        std::cout << game_result.error() << std::endl;
    }

    auto game = game_result.value();

    return 0;
}