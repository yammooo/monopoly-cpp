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

bool is_game_ended(GameData* game)
{
    int players_in_game = 0;
    for(int i = 0; i < game->board()->get_player_number(); i++)
    {
        if(game->board()->player(i)->is_in_game())
        {
            players_in_game++;
        }
    }
    // If there's only one player left in the game, the game has ended
    return players_in_game == 1;
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


    int players_in_game = 0;
    std::cout << "\nPlayers in game: ";
    for(int i = 0; i < game->board()->get_player_number(); i++)
    {
        if(game->board()->player(i)->is_in_game())
        {
            players_in_game++;
            std::cout << game->board()->player(i)->id() << " ";
        }
    }
    std::cout << "\nTotal: " << players_in_game << "\n";


    std::cout << "Player " << player_index << " is throwing dice\n";

    auto dice_result = random->get_next(1, 6) + random->get_next(1, 6);

    std::cout << "Player " << player_index << " rolled a " << dice_result << "\n";

    auto old_position = game->board()->player(player_index)->position();

    auto new_position = (old_position + dice_result) % game->configuration().board_size();

    std::cout << "Player " << player_index << " moved from " << old_position << " to " << new_position << "\n";

    game->board()->player(player_index)->position(new_position);

    if (new_position < old_position)
    {
        game->board()->player(player_index)->credit(game->configuration().start_prize());
        std::cout << "Player " << player_index << " has now " << game->board()->player(player_index)->coins() << ".\n";
    }

    auto tile = game->board()->tile(new_position);

    auto tile_category = tile.category();

    if (tile_category == TileCategory::Corner || tile_category == TileCategory::Start)
    {   
        game->board()->next_round();
    }
    else if (tile_category == TileCategory::Cheap || tile_category == TileCategory::Standard || tile_category == TileCategory::Luxury)
    {   
        // If the tile is not owned by anyone
        if (tile.owner_id() == -1)
        {
            std::cout << "Player " << player_index << " is on a tile that is not owned.\n";
            auto buy_price = game->configuration().get_prize(PaymentAction::BuyLand, tile_category);
            
            // If the player has enough coins
            if (game->board()->player(player_index)->coins() >= buy_price)
            {
                std::cout << "Player " << player_index << " has " << game->board()->player(player_index)->coins() << " can buy a tile for " << buy_price << "\n";
                game->board()->state(GameState::PlayerPayment);
            }
        }
        else
        {   
            // If the player is the owner of the tile and the tile is not a hotel
            if (player_index == tile.owner_id())
            {   
                std::cout << "Player " << player_index << " is on a tile that is owned by him.\n";
                auto upgrade_cost = game->configuration().get_prize(tile.housing() == TileHousing::Land ? PaymentAction::BuyHouse : PaymentAction::BuyHotel, tile.category());
                
                // Check if the player has enough coins for the upgrade and the current housing is not a Hotel (since a Hotel is the highest upgrade)
                if ((game->board()->player(player_index)->coins() >= upgrade_cost) && (tile.housing() < TileHousing::Hotel))
                {
                    std::cout << "Player " << player_index << " can upgrade the tile.\n";
                    game->board()->state(GameState::PlayerPayment);
                }

            }
            // If the player is not the owner of the tile and the tile is not a land
            else if (tile.housing() == TileHousing::House || tile.housing() == TileHousing::Hotel)
            {   
                std::cout << "Player " << player_index << " is on a tile that is owned by someone else.\n";
                std::cout << "Player " << player_index << " has to pay rent.\n";

                auto payment_action = tile.housing() == TileHousing::House ? PaymentAction::HouseStay : PaymentAction::HotelStay;
                
                auto payment = game->configuration().get_prize(payment_action, tile.category());

                game->board()->player(player_index)->debit(payment);
                std::cout << "Player " << player_index << " has now " << game->board()->player(player_index)->coins() << ".\n";

                auto player_coins = game->board()->player(player_index)->coins();

                if (player_coins < 0)
                {
                    payment += player_coins;
                }

                game->board()->player(tile.owner_id())->credit(payment);
                std::cout << "Player " << player_index << " coins: " << player_coins << "\n";

                if (player_coins < 0)
                {
                    std::cout << "Player " << player_index << " is bankrupt.\n";
                    std::cout << "Player " << player_index << " has now " << game->board()->player(player_index)->coins() << ".\n";

                    if(is_game_ended(game))
                    {
                        game->board()->state(GameState::Ended);
                        return GameInfo(*game);
                    }

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
            // If the player is not the owner of the tile and the tile is a land
            else
            {   
                std::cout << "Player " << player_index << " is on a tile that is owned by someone else.\n";
                game->board()->next_round();
            }
        }
    }
    else
    {
        throw std::exception();
    }

    return GameInfo(*game);
}

GameInfo process_player_payment(GameData* game, ActionInfo action)
{
    if (action.type() != ActionType::AcceptPayment && action.type() != ActionType::DenyPayment)
    {
        throw std::exception();
    }

    std::cout << "Processing payment...\n";

    if (action.type() == ActionType::DenyPayment)
    {
        std::cout << "Player " << game->board()->player_turns().at(game->board()->round() % game->board()->get_player_number()) << " denied the payment.\n";
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
                std::cout << "Player " << player_index << " bought a house.\n";
            } else {
                game->board()->tile(player_position).set_property(player_index);
                std::cout << "Player " << player_index << " bought a land.\n";
            }
            break;
        }
        case TileHousing::House:
        {
            game->board()->tile(player_position).housing(TileHousing::Hotel);
            std::cout << "Player " << player_index << " upgraded to a hotel.\n";
            break;
        }
        default:
            throw std::exception();
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