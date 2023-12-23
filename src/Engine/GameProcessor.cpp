#include "../../include/Engine/GameProcessor.h"

using namespace object_models;
using namespace dependency_injection;

GameInfo engine::GameProcessor::process(GameData* game, ActionInfo action)
{
    return GameInfo(game->id());
}

engine::GameProcessor::GameProcessor()
{
    _random = ServiceProvider::get_service<RandomContext>();
}