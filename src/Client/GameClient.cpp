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

    while (info.state() != GameState::Ended) // while che fa andare tutta la simulazione
    {
        player_index = 0; // ---> new! info.current_turn(); ---> OLD // player_turns().at(info.round() % info.player_number());

        action = _players[player_index]->get_action(info);  // passi al player le informazioni del gioco e gli chiedi cosa vuole fare

        auto result = _context->play(info.id(), action); // vai sul context e fai un'azione 

        //qua stampo i log --- ma auto result gioca solo 1 turno? cosa fa? 

        if (result.isError())
        {
            // TODO fai qualcosa
        }

        info = result.value();
    }

    std::cout << "The winner is player " << info.winner() << std::endl;
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
