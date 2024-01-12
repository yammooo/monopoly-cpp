// Author: Gianmaria Frigo

#include "../../include/Engine/GameProcessor.h"
#include "../../include/Engine/GameLogger.h"
#include <stdexcept>

using namespace object_models;
using namespace dependency_injection;
using namespace object_states;
using namespace engine;

// Function to find keys in the input map that have the same value
std::vector<int> find_keys_with_duplicate_values(const std::map<int, int>& inputMap)
{  
    // Map that stores the values from the input map as keys
    std::unordered_map<int, std::vector<int>> valueToKeysMap;

    for (const auto& pair : inputMap)
    {
        valueToKeysMap[pair.second].push_back(pair.first);
    }

    std::vector<int> output;

    // Find keys with duplicate values
    for (const auto& pair : valueToKeysMap)
    {
        // If more than one key has the same value, add them to the output vector
        if (pair.second.size() > 1)
        {
            output.insert(output.end(), pair.second.begin(), pair.second.end());
        }
    }

    return output;
}

// Function to get keys from the input map sorted by their values
std::vector<int> get_keys_sorted_by_values(const std::map<int, int>& inputMap)
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

// Function to check if the game has ended
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

// Function to get the index of the winner
int winner_index(GameData* game)
{
    int winner = -1;
    for(int i = 0; i < game->board()->get_player_number(); i++)
    {
        if(game->board()->player(i)->is_in_game())
        {
            winner=i;
        }
    }
    return winner;
}

GameInfo process_player_dice_throw(GameData* game, ActionInfo action, engine::RandomContext* random)
{
    GameLogger _logger;

    // Check if the action type is ThrowDice
    if (action.type() != ActionType::ThrowDice)
    {
        throw std::invalid_argument("Expected ThrowDice action type in GameProcessor::process_player_dice_throw method");
    }

    auto player_index = game->board()->player_turns().get_current_player_index();

    // Get the current player's coins
    auto player_coins = game->board()->player(player_index)->coins();

    // Generate a random dice result
    auto dice_result = random->get_next(1, 6) + random->get_next(1, 6);

    _logger.log_action("- Giocatore " + std::to_string(player_index) + " ha tirato i dadi ottenendo un valore di " + std::to_string(dice_result));

    // Calculate the new position based on the dice result
    auto old_position = game->board()->player(player_index)->position();
    auto new_position = (old_position + dice_result) % game->configuration().board_size();

    // Get the tile at the new position
    auto tile = game->board()->tile(new_position);
    auto tile_category = tile.category();

    _logger.log_action("- Giocatore " + std::to_string(player_index) + " è arrivato alla casella " + tile.name());

    // Update the player's position
    game->board()->player(player_index)->position(new_position);

    // Check if the player passed the Start tile
    if (new_position < old_position)
    {
        // Credit the player with the start prize
        auto start_prize = game->configuration().start_prize();
        game->board()->player(player_index)->credit(start_prize);

        _logger.log_action("- Giocatore " + std::to_string(player_index) + " è passato dal via e ha ritirato " + std::to_string(start_prize) + " fiorini");
    }

    if (tile_category == TileCategory::Corner || tile_category == TileCategory::Start)
    {
        // If the tile is a corner or start tile go to the next round
        game->board()->next_round();
    }
    else if (tile_category == TileCategory::Cheap || tile_category == TileCategory::Standard || tile_category == TileCategory::Luxury)
    {
        // If the tile is not owned by anyone
        if (tile.owner_id() == -1)
        {
            auto buy_price = game->configuration().get_prize(PaymentAction::BuyLand, tile_category);
            
            // If the player has enough coins
            if (game->board()->player(player_index)->coins() >= buy_price)
            {
                game->board()->state(GameState::PlayerBuyLand);
            }
            else
            {
                // If the player doesn't have enough coins, move to the next round
                game->board()->next_round();
            }
        }
        // If the tile is owned by someone
        else
        {
            // If the player is the owner of the tile
            if (player_index == tile.owner_id())
            {
                auto upgrade_cost = game->configuration().get_prize(tile.housing() == TileHousing::Land ? PaymentAction::BuyHouse : PaymentAction::BuyHotel, tile_category);
                
                // Check if the player has enough coins for the upgrade and the current housing is not a Hotel (since a Hotel is the highest upgrade)
                if ((game->board()->player(player_index)->coins() >= upgrade_cost) && (tile.housing() == TileHousing::House || tile.housing() == TileHousing::Land))
                {
                    if (tile.housing() == TileHousing::Land)
                    {
                        game->board()->state(GameState::PlayerBuyHouse);
                    }
                    else
                    {
                        game->board()->state(GameState::PlayerBuyHotel);
                    }
                }
                else
                {
                    game->board()->next_round();
                }
            }
            // If the player is not the owner of the tile and the tile is not a land they have to pay rent
            else if (tile.housing() == TileHousing::House || tile.housing() == TileHousing::Hotel)
            {   

                auto payment_action = tile.housing() == TileHousing::House ? PaymentAction::HouseStay : PaymentAction::HotelStay;
                
                auto payment = game->configuration().get_prize(payment_action, tile.category());

                // Debit the rent to the player
                game->board()->player(player_index)->debit(payment);

                auto player_coins = game->board()->player(player_index)->coins();


                if (player_coins < 0)
                {   
                    // The player doesn't have enough coins to cover the full rent.
                    // We decided that in this case the player pays as much as he has.
                    payment += player_coins;
                }

                game->board()->player(tile.owner_id())->credit(payment);

                // If the player doesn't have enough coins to pay the rent, they go bankrupt
                if (player_coins < 0)
                {
                    game->board()->remove_player(player_index);

                    _logger.log_action("- Giocatore "+std::to_string(player_index)+" é stato eliminato");

                    if(is_game_ended(game))
                    {
                        _logger.log_action("- Giocatore "+ std::to_string(winner_index(game))+" ha vinto la partita ");
                        game->board()->state(GameState::Ended);
                        return GameInfo(*game, _logger);
                    }

                    // Reset all the tiles owned by the bankrupt player
                    for (int i = 0; i < game->configuration().board_size(); i++)
                    {
                        if (game->board()->tile(i).owner_id() == player_index)
                        {
                            game->board()->tile(i).set_property(-1);
                            game->board()->tile(i).housing(TileHousing::Land);
                        }
                    }
                }
                else{
                    _logger.log_action("- Giocatore "+ std::to_string(player_index)+" ha pagato "+ std::to_string(payment)+" al giocatore "+ std::to_string(tile.owner_id())+ " per pernottamento nella casella " + tile.name()) ;
                }
                game->board()->next_round();
            }
            // If the player is not the owner of the tile and the tile is a land
            else
            {   
                //std::cout << "Player " << player_index << " is on a land tile that is owned by someone else.\n";
                game->board()->next_round();
            }
        }
    }
    else
    {
        throw std::invalid_argument("Unexpected TileCategory in GameProcessor::process_player_dice_throw");
    }

    return GameInfo(*game, _logger );
}

GameInfo process_player_payment(GameData* game, ActionInfo action)
{   
    GameLogger _logger;

    auto player_index = game->board()->player_turns().get_current_player_index();
    

    if (action.type() != ActionType::AcceptPayment && action.type() != ActionType::DenyPayment)
    {
        throw std::invalid_argument("Invalid action type provided to GameProcessor::process_player_payment. Expected AcceptPayment or DenyPayment.");
    }

    if (action.type() == ActionType::DenyPayment)
    {
        // If the action type is DenyPayment,
        // move to the next round and set the game state to PlayerDiceThrow
        game->board()->next_round();
        game->board()->state(GameState::PlayerDiceThrow);
        return GameInfo(*game, _logger);
    }
    
    auto player_position = game->board()->player(player_index)->position();
    auto tile = game->board()->tile(player_position);

    // Check the housing type of the tile
    switch (tile.housing())
    {
        case TileHousing::Land:
        {
            if (tile.owner_id() == player_index)
            {
                // If the player is the owner of the land it buys a house
                auto payment = game->configuration().get_prize(PaymentAction::BuyHouse, tile.category());
                game->board()->player(player_index)->debit(payment);

                // Upgrade the land to a house
                game->board()->tile(player_position).housing(TileHousing::House);

                _logger.log_action("- Giocatore "+ std::to_string(player_index)+ " ha costruito una casa sul terreno " + tile.name());

            } else {
                // If the player is not the owner of the land it buys the land
                auto payment = game->configuration().get_prize(PaymentAction::BuyLand, tile.category());
                game->board()->player(player_index)->debit(payment);
                
                // Set the player as the owner of the land
                game->board()->tile(player_position).set_property(player_index);

                _logger.log_action("- Giocatore "+ std::to_string(player_index)+ " ha acquistato il terreno " + tile.name());
                
            }
            break;
        }
        case TileHousing::House:
        {   
            // If the tile is a house, the player buys a hotel
            auto payment = game->configuration().get_prize(PaymentAction::BuyHotel, tile.category());
            game->board()->player(player_index)->debit(payment);

            // Upgrade the house to a hotel
            game->board()->tile(player_position).housing(TileHousing::Hotel);

            _logger.log_action("- Giocatore "+ std::to_string(player_index)+ " ha migliorato una casa in albergo sul terreno " + tile.name());
            break;
        }
        default:
            throw std::invalid_argument("Invalid tile housing type encountered in GameProcessor::process_player_payment method");
            break;
    }

    // Move to the next round and set the game state to PlayerDiceThrow
    game->board()->next_round();
    game->board()->state(GameState::PlayerDiceThrow);

    return GameInfo(*game, _logger);
}

GameInfo engine::GameProcessor::process(GameData* game, ActionInfo action)
{   
    GameState state = game->board()->state();

    if (state == GameState::PlayerDiceThrow)
    {
        return process_player_dice_throw(game, action, _random);
    }
    else if ((state == GameState::PlayerBuyLand) || (state == GameState::PlayerBuyHouse) || (state == GameState::PlayerBuyHotel))
    {
        return process_player_payment(game, action);
    }

    throw std::invalid_argument("Invalid GameState in GameProcessor::process method");
}

object_models::GameInfo engine::GameProcessor::init_game(object_models::GameData* game)
{
    int playerNumber = game->configuration().player_number();

    std::map<int, int> pointsByPlayer;

    // Assign random points to each player
    for (int i = 0; i < playerNumber; i++)
    {
        pointsByPlayer[i] = _random->get_next(1, 6) + _random->get_next(1, 6);
    }

    std::vector<int> keys = find_keys_with_duplicate_values(pointsByPlayer);
    
    // Continue assigning random points until all players have unique points
    do
    {
        for (int i = 0; i < keys.size(); i++)
        {
            pointsByPlayer[keys[i]] = _random->get_next(1, 6) + _random->get_next(1, 6);
        }

        keys = find_keys_with_duplicate_values(pointsByPlayer);

    } while (keys.size() > 0);

    std::vector<int> sortedPlayers = get_keys_sorted_by_values(pointsByPlayer);

    // Set the player turns based on the sorted players
    game->board()->player_turns(sortedPlayers);

    std::vector<PlayerData> newPlayers {};

    // Create PlayerData for each player
    for (int i = 0; i < playerNumber; i++)
    {
        newPlayers.push_back(PlayerData(i, 0, game->configuration().initial_balance()));
    }

    game->board()->players(newPlayers);

    // Return the updated GameInfo
    return GameInfo(*game);
};

engine::GameProcessor::GameProcessor()
{
    _random = ServiceProvider::get_service<RandomContext>();
}