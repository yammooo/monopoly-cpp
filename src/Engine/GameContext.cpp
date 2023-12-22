#include "../../include/Engine/GameContext.h"

using namespace engine;
using namespace object_models;
using namespace dependency_injection;

engine::GameContext::GameContext()
{
    _repository = ServiceProvider::get_service<GameRepository>();
    _processor = ServiceProvider::get_service<GameProcessor>();

    _nextId = 0;
}

int engine::GameContext::create_game()
{
    auto id = _nextId++;

    auto game = GameData(id, GameConfiguration::get_default());

    _repository.save_game(game);

    return id;
}