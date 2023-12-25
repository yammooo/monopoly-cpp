#include "../../include/Client/GameClient.h"

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
        throw std::exception();
    }

    ActionInfo action;
    int player_index;

    while (info.state() != GameState::Ended)
    {
        player_index = info.player_turns().at(info.round() % info.player_number());

        action = _players[player_index]->get_action(info);

        auto result = _context->play(info.id(), action);

        if (result.isError())
        {
            // Todo fai qualcosa
        }

        info = result.value();
    }
}

client::GameClient::GameClient()
{
    _configuration = GameConfiguration::get_default();
    _context = ServiceProvider::get_service<GameContext>();
}

void client::GameClient::execute(std::vector<IPlayer*> players)
{
    _players = players;

    auto info_result = _context->create_game();

    if (info_result.isError())
    {
        throw std::exception();
    }

    auto info = info_result.value();

    execute_inner(info);
}

void client::GameClient::execute(std::vector<IPlayer*> players, GameConfiguration configuration)
{
    _players = players;

    auto info_result = _context->create_game(configuration);

    if (info_result.isError())
    {
        throw std::exception();
    }

    auto info = info_result.value();

    execute_inner(info);
}
