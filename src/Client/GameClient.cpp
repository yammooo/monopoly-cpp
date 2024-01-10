// Author: Gianmaria Frigo

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


// This function is responsible for executing the game logic.
void client::GameClient::execute_inner(object_models::GameInfo info)
{
    // Check if the player number in the configuration matches the player number in the game info.
    // If they don't match, throw a PlayerNumberMismatchException.
    if (_configuration.player_number() != info.player_number())
    {
        throw PlayerNumberMismatchException();
    }

    ActionInfo action;
    int player_index;

    // Open a log file for writing.
    std::ofstream log_file("../log.txt");

    // Continue the game until the game is ended or the maximum round limit is reached.
    while ((info.state() != GameState::Ended) && (info.round() < _configuration.max_round()))
    {
        int player_index = info.player_turns().get_current_player_index();

        // Get the action to be performed by the current player.
        action = _players[player_index]->get_action(info);

        // Play the action in the game context and get the updated game info.
        auto result = _context->play(info.id(), action);

        // If an error occurred during the action execution, throw a runtime error.
        if (result.isError())
        {
            throw std::runtime_error(result.error());
        }

        // Update the game info with the result of the action.
        info = result.value();

        // Print the game log to the terminal.
        std::cout << info.log_to_string();

        // Write the game log to the log file.
        log_file << info.log_to_string();
    }

    log_file.close();
}

client::GameClient::GameClient()
{
    // Set the configuration to the default game configuration.
    _configuration = GameConfiguration::get_default();

    // Get the game context from the service provider.
    _context = ServiceProvider::get_service<GameContext>();
}

// Execute the game with the given players.
void client::GameClient::execute(std::vector<std::shared_ptr<IPlayer>> players)
{
    _players = players;

    // Create a new game using the game context.
    Result<GameInfo> info_result = _context->create_game();

    // If an error occurred during game creation, throw a runtime error.
    if (info_result.isError())
    {
        throw std::runtime_error(info_result.error());
    }

    // Get the game info from the result.
    GameInfo info = info_result.value();

    // Execute the game logic.
    execute_inner(info);
}

// Execute the game with the given players and configuration.
void client::GameClient::execute(std::vector<std::shared_ptr<IPlayer>> players, GameConfiguration configuration)
{
    _players = players;

    // Create a new game using the game context and the given configuration.
    Result<object_models::GameInfo> info_result = _context->create_game(configuration);

    // If an error occurred during game creation, throw a runtime_error.
    if (info_result.isError())
    {
        throw std::runtime_error(info_result.error());
    }

    // Get the game info from the result.
    GameInfo info = info_result.value();

    // Execute the game logic.
    execute_inner(info);
}