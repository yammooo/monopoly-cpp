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

    auto player_index = game->board()->player_turns().at(game->board()->round() % game->board()->get_player_number());

    if (!game->board()->player(player_index)->is_in_game())
    {
        game->board()->next_round();
        
        return GameInfo(*game);
    }

    auto dice_result = random->get_next(1, 6) + random->get_next(1, 6);

    auto old_position = game->board()->player(player_index)->position();

    auto new_position = (old_position + dice_result) % game->configuration().board_size();

    game->board()->player(player_index)->position(new_position);

    if (new_position < old_position)
    {
        game->board()->player(player_index)->credit(game->configuration().start_prize());
    }

    auto tile = game->board()->tile(new_position);

    auto tile_category = tile.category();

    if (tile_category == TileCategory::Corner || tile_category == TileCategory::Start)
    {
        game->board()->next_round();
    }
    
    if (tile_category == TileCategory::Cheap || tile_category == TileCategory::Standard || tile_category == TileCategory::Luxury)
    {
        if (tile.owner_id() == -1)
        {
            auto buy_price = game->configuration().get_prize(PaymentAction::BuyLand, tile_category);

            if (game->board()->player(player_index)->coins() >= buy_price)
            {
                game->board()->state(GameState::PlayerPayment);
            }
        }
        else
        {
            if (player_index == tile.owner_id())
            {
                if (tile.housing() < TileHousing::Hotel)
                {
                    game->board()->state(GameState::PlayerPayment);
                }
            }
            else if (tile.housing() == TileHousing::House || tile.housing() == TileHousing::Hotel)
            {
                auto payment_action = tile.housing() == TileHousing::House ? PaymentAction::HouseStay : PaymentAction::HotelStay;
                
                auto payment = game->configuration().get_prize(payment_action, tile.category());

                game->board()->player(player_index)->debit(payment);

                auto player_coins = game->board()->player(player_index)->coins();

                if (player_coins < 0)
                {
                    payment += player_coins;
                }

                game->board()->player(tile.owner_id())->credit(payment);
                std::cout << "Player " << player_index << " coins: " << player_coins << "\n";

                if (player_coins < 0)
                {
                    for (int i = 0; i < game->configuration().board_size(); i++)
                    {
                        if (game->board()->tile(i).owner_id() == player_index)
                        {
                            game->board()->tile(i).set_property(-1);
                            game->board()->tile(i).housing(TileHousing::Land);
                        }
                    }


                    game->board()->next_round();
                }
            }
        }
    }

    return GameInfo(*game);
}

GameInfo process_player_payment(GameData* game, ActionInfo action)
{
    if (action.type() != ActionType::AcceptPayment && action.type() != ActionType::DenyPayment)
    {
        throw std::exception();
    }

    if (action.type() == ActionType::DenyPayment)
    {
        game->board()->next_round();
        game->board()->state(GameState::PlayerDiceThrow);

        return GameInfo(*game);
    }

    auto player_index = game->board()->player_turns().at(game->board()->round() % game->board()->get_player_number());

    auto player_position = game->board()->player(player_index)->position();

    auto tile = game->board()->tile(player_position);

    auto payment_action = tile.housing() == TileHousing::Land ? PaymentAction::BuyLand : tile.housing() == TileHousing::House ? PaymentAction::BuyHouse : PaymentAction::BuyHotel;

    auto price = game->configuration().get_prize(payment_action, tile.category());

    game->board()->player(player_index)->debit(price);

    switch (tile.housing())
    {
        case TileHousing::Land:
        {
            if (tile.owner_id() == player_index)
            {
                game->board()->tile(player_position).housing(TileHousing::House);
            }
            break;
        }
        case TileHousing::House:
        {
            game->board()->tile(player_position).housing(TileHousing::Hotel);
            break;
        }
        default:
            break;
    }

    game->board()->tile(player_position).set_property(player_index);

    game->board()->next_round();
    game->board()->state(GameState::PlayerDiceThrow);

    return GameInfo(*game);
}

GameInfo engine::GameProcessor::process(GameData* game, ActionInfo action)
{
    switch (game->board()->state())
    {
        case GameState::PlayerDiceThrow:
            return process_player_dice_throw(game, action, _random);
        case GameState::PlayerPayment:
            return process_player_payment(game, action);
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