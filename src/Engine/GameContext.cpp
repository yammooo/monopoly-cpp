#include "../../include/Engine/GameContext.h"

using namespace engine;
using namespace object_models;
using namespace dependency_injection;

GameContext::GameContext()
{
    _repository = ServiceProvider::get_service<GameRepository>();
    _processor = ServiceProvider::get_service<GameProcessor>();

    _nextId = 0;
}

GameContext::GameContext(const GameContext& other)
{
    _repository = other._repository;
    _processor = other._processor;
    _nextId = other._nextId; 
}

Result<GameInfo> GameContext::create_game()
{
    try
    {
        auto id = _nextId++;

        // MEMORY LEAK OH MY GOD

        auto game = new GameData(id, GameConfiguration::get_default());

        auto info = _processor->init_game(game);
        
        _repository->save_game(*game);

        return Result<GameInfo>::Ok(info);
    }
    catch(const std::exception& e)
    {
        // TODO: Log exception
    }
     
    return Result<GameInfo>::Error("Error while creating new game");
}

Result<GameInfo> GameContext::create_game(GameConfiguration configuration)
{
    try
    {
        auto id = _nextId++;

        auto game = GameData(id, configuration);

        auto info = _processor->init_game(&game);

        return Result<GameInfo>::Ok(info);
    }
    catch (const std::exception& e)
    {
        // TODO: Log exception
    }

    return Result<GameInfo>::Error("Error while creating new game");
}

Result<GameInfo> GameContext::play(int id, ActionInfo info)
{
    try
    {
        auto game = _repository->get_game(id);

        auto result = _processor->process(&game, info);

        _repository->save_game(game);

        return Result<GameInfo>::Ok(result);
    }
    catch(const std::exception& e)
    {
        // TODO: Log exception
    }
    
    return Result<GameInfo>::Error("Error while performing action on game");
}