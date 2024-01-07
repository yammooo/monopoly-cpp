#include "../../include/ObjectModels/GameData.h"

using namespace object_models;

GameData::GameData(int id, GameConfiguration configuration)
{
    _id = id;
    _configuration = configuration;
    
    std::vector<PlayerData> players;

    for (int i = 0; i < configuration.player_number(); i++)
    {
        players.push_back(PlayerData(i, 0, configuration.initial_balance()));
    }

    _board = GameBoard(configuration.tiles(), players);

    // TODO: Add board configured as configuration says :)
}

std::string object_models::GameData::board_to_string() const
{
    
}