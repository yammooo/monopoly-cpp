#include "../../include/Engine/GameProcessor.h"

using namespace object_models;
using namespace dependency_injection;

std::vector<int> find_keys(const std::map<int, int>& inputMap)
{
    std::unordered_map<int, std::vector<int>> valueToKeysMap;

    for (const auto& pair : inputMap)
    {
        valueToKeysMap[pair.second].push_back(pair.first);
    }

    std::vector<int> result;

    for (const auto& pair : valueToKeysMap)
    {
        if (pair.second.size() > 1)
        {
            result.insert(result.end(), pair.second.begin(), pair.second.end());
        }
    }

    return result;
}

std::vector<int> get_keys(const std::map<int, int>& inputMap)
{
    std::vector<int> keys {};

    std::multimap<int, int> valueToKeyMap;

    for (const auto& pair : inputMap)
    {
        valueToKeyMap.insert({pair.second, pair.first});
    }

    for (const auto& pair : valueToKeyMap)
    {
        keys.push_back(pair.second);
    }

    return keys;
}

GameInfo engine::GameProcessor::process(GameData* game, ActionInfo action)
{

    return GameInfo(game->id());
}

object_models::GameInfo engine::GameProcessor::init_game(object_models::GameData* game)
{
    int playerNumber = game->configuration().playerNumber();

    std::map<int, int> pointsByPlayer;

    for (int i = 0; i < playerNumber; i++)
    {
        pointsByPlayer[i] = _random->get_next(1, 6) + _random->get_next(1, 6);
    }

    auto keys = find_keys(pointsByPlayer);
    
    do
    {
        for (int i = 0; i < keys.size(); i++)
        {
            pointsByPlayer[keys[i]] = _random->get_next(1, 6) + _random->get_next(1, 6);
        }

        keys = find_keys(pointsByPlayer);

    } while (keys.size() > 0);

    auto sortedPlayers = get_keys(pointsByPlayer);

    game->board().playerTurns(sortedPlayers);

    std::vector<Player> new_players {};

    for (int i = 0; i < playerNumber; i++)
    {
        new_players.push_back(Player(i, 0, game->configuration().initialBalance()));
    }

    game->board().players(new_players);

    return GameInfo(1);
};

engine::GameProcessor::GameProcessor()
{
    _random = ServiceProvider::get_service<RandomContext>();
}