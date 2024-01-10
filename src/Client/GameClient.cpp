#include <iostream>
#include <fstream>

#include "../../include/Client/GameClient.h"
#include "../../include/Engine/GameLogger.h"
#include "../../include/Client/PlayerNumberMismatchException.h"

using namespace client;
using namespace engine;
using namespace object_states;
using namespace object_models;
using namespace dependency_injection;
using namespace interfaces;

void client::GameClient::execute_inner(object_models::GameInfo info)
{
    if (_configuration.player_number() != info.player_number())
    {
        throw PlayerNumberMismatchException();
    }

    ActionInfo action;
    int player_index;

    std::ofstream log_file("../log.txt");

    while ((info.state() != GameState::Ended) && (info.round() < _configuration.max_round()))
    {
        int player_index = info.player_turns().get_current_player_index();

        action = _players[player_index]->get_action(info);

        auto result = _context->play(info.id(), action);

        if (result.isError())
        {
            throw std::runtime_error(result.error());
        }

        info = result.value();

        std::cout << info.log_to_string(); // Print to terminal
        log_file << info.log_to_string(); // Write to file

    }

    log_file.close();
}

client::GameClient::GameClient()
{
    _configuration = GameConfiguration::get_default();
    _context = ServiceProvider::get_service<GameContext>();
}

void client::GameClient::execute(std::vector<std::shared_ptr<IPlayer>> players)
{
    _players = players;

    auto info_result = _context->create_game();

    if (info_result.isError())
    {
        throw std::runtime_error(info_result.error());
    }

    auto info = info_result.value();

    execute_inner(info);
}

void client::GameClient::execute(std::vector<std::shared_ptr<IPlayer>> players, GameConfiguration configuration)
{
    _players = players;

    Result<object_models::GameInfo> info_result = _context->create_game(configuration);

    if (info_result.isError())
    {
        throw std::runtime_error(info_result.error());
    }

    GameInfo info = info_result.value();

    execute_inner(info);
}
