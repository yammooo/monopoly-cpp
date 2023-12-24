#include "../../include/Engine/GameProcessor.h"

using namespace object_models;
using namespace dependency_injection;
using namespace object_states;

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

GameInfo process_player_dice_throw(GameData* game, ActionInfo action, engine::RandomContext* random)
{
    if (action.type() != ActionType::ThrowDice)
    {
        throw std::exception();
    }

    auto dice_result = random->get_next(1, 6) + random->get_next(1, 6);

    return GameInfo(game->id());
}

GameInfo engine::GameProcessor::process(GameData* game, ActionInfo action)
{
    switch (game->board()->state())
    {
        case GameState::PlayerDiceThrow:
            return process_player_dice_throw(game, action, _random);
        default:
            break;
    }

    return GameInfo(*game);
}

object_models::GameInfo engine::GameProcessor::init_game(object_models::GameData* game)
{
    int playerNumber = game->configuration().player_number();

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

    game->board()->player_turns(sortedPlayers);

    std::vector<PlayerData> new_players {};

    for (int i = 0; i < playerNumber; i++)
    {
        new_players.push_back(PlayerData(i, 0, game->configuration().initial_balance()));
    }

    game->board()->players(new_players);

    return GameInfo(*game);
};

engine::GameProcessor::GameProcessor()
{
    _random = ServiceProvider::get_service<RandomContext>();
}