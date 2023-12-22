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

engine::GameContext::GameContext(const engine::GameContext& other)
{
    _repository = other._repository;
    _processor = other._processor;
    _nextId = other._nextId; 
}

Result<GameInfo> engine::GameContext::create_game()
{
    try
    {
        auto id = _nextId++;

        auto game = GameData(id, GameConfiguration::get_default());

        return Result<GameInfo>::Ok(GameInfo(id));
    }
    catch(const std::exception& e)
    {
        // TODO: Log exception
    }
    
    return Result<GameInfo>::Error("Error while creating new game");
}