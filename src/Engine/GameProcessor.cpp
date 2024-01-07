#include "../../include/Engine/GameProcessor.h"
#include "../../include/Engine/GameLogger.h"
#include <stdexcept>

using namespace object_models;
using namespace dependency_injection;
using namespace object_states;
using namespace engine;

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
    // If there's only one player left in the game, the game has ended
    return winner;
}

GameInfo process_player_dice_throw(GameData* game, ActionInfo action, engine::RandomContext* random)
{

    GameLogger _logger; 

    if (action.type() != ActionType::ThrowDice)
    {
        throw std::exception();
    }

    auto player_index = game->board()->player_turns().get_current_player_index();

    if (!game->board()->player(player_index)->is_in_game())
    {
        game->board()->next_round();
        
        return GameInfo(*game, _logger);
    }


    int players_in_game = 0;
    //std::cout << "\nPlayers in game: ";
    for(int i = 0; i < game->board()->get_player_number(); i++)
    {
        if(game->board()->player(i)->is_in_game())
        {
            players_in_game++;
            //std::cout << game->board()->player(i)->id() << " ";
        }
    }
    //std::cout << "\nTotal: " << players_in_game << "\n";


    //std::cout << "Player " << player_index << " is throwing dice and has " << game->board()->player(player_index)->coins() << " coins.\n";

    auto dice_result = random->get_next(1, 6) + random->get_next(1, 6);

    _logger.log_action("- Giocatore "+ std::to_string(player_index)+" ha tirato i dadi ottenendo un valore di "+ std::to_string(dice_result));

    //std::cout << "Player " << player_index << " rolled a " << dice_result << "\n";

    auto old_position = game->board()->player(player_index)->position();

    auto new_position = (old_position + dice_result) % game->configuration().board_size();

    _logger.log_action("- Giocatore "+ std::to_string(player_index)+" é arrivato alla casella "+ std::to_string(new_position));

    //std::cout << "Player " << player_index << " moved from " << old_position << " to " << new_position << "\n";

    game->board()->player(player_index)->position(new_position);

    if (new_position < old_position)
    {
        game->board()->player(player_index)->credit(game->configuration().start_prize());

        _logger.log_action("- Giocatore "+std::to_string(player_index)+" é passato dal via e ha ritirato "+ std::to_string(game->configuration().start_prize())+ " fiorini");
        //std::cout << "Player " << player_index << " has now " << game->board()->player(player_index)->coins() << ".\n";
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
            //std::cout << "Player " << player_index << " is on a tile that is not owned by anyone.\n";
            auto buy_price = game->configuration().get_prize(PaymentAction::BuyLand, tile_category);
            
            // If the player has enough coins
            if (game->board()->player(player_index)->coins() >= buy_price)
            {
                //std::cout << "Player " << player_index << " has " << game->board()->player(player_index)->coins() << " can buy a tile for " << buy_price << "\n";
                game->board()->state(GameState::PlayerBuyLand);
            } else {
                //std::cout << "Player " << player_index << " has " << game->board()->player(player_index)->coins() << " can't buy a tile for " << buy_price << "\n";
                game->board()->next_round();
            }
        }
        // If the tile is owned by someone
        else
        {
            // If the player is the owner of the tile
            if (player_index == tile.owner_id())
            {
                //std::cout << "Player " << player_index << " is on a tile that is owned by him.\n";
                auto upgrade_cost = game->configuration().get_prize(tile.housing() == TileHousing::Land ? PaymentAction::BuyHouse : PaymentAction::BuyHotel, tile_category);
                
                // Check if the player has enough coins for the upgrade and the current housing is not a Hotel (since a Hotel is the highest upgrade)
                if ((game->board()->player(player_index)->coins() >= upgrade_cost) && (tile.housing() == TileHousing::House || tile.housing() == TileHousing::Land))
                {
                    if (tile.housing() == TileHousing::Land)
                    {
                        game->board()->state(GameState::PlayerBuyHouse);
                    }else
                    {
                        game->board()->state(GameState::PlayerBuyHotel);
                    }
                }
                else if (tile.housing() == TileHousing::Hotel)
                {
                    //std::cout << "Player " << player_index << " can't upgrade the tile because it is already an hotel.\n";
                    game->board()->next_round();
                }
                else
                {
                    //std::cout << "Player " << player_index << " can't upgrade the tile because he has " << game->board()->player(player_index)->coins() << " coins.\n";
                    game->board()->next_round();
                }

            }
            // If the player is not the owner of the tile and the tile is not a land
            else if (tile.housing() == TileHousing::House || tile.housing() == TileHousing::Hotel)
            {   
                //std::cout << "Player " << player_index << " is on a tile that is owned by someone else.\n";
                //std::cout << "Player " << player_index << " has to pay rent.\n";

                auto payment_action = tile.housing() == TileHousing::House ? PaymentAction::HouseStay : PaymentAction::HotelStay;
                
                auto payment = game->configuration().get_prize(payment_action, tile.category());

                game->board()->player(player_index)->debit(payment);
                //std::cout << "Player " << player_index << " has now " << game->board()->player(player_index)->coins() << ".\n";

                auto player_coins = game->board()->player(player_index)->coins();

                if (player_coins < 0)
                {
                    payment += player_coins;
                }

                game->board()->player(tile.owner_id())->credit(payment);

                if (player_coins < 0)
                {
                    //std::cout << "Player " << player_index << " is bankrupt.\n";

                    _logger.log_action("- Giocatore "+std::to_string(player_index)+" é stato eliminato");

                    if(is_game_ended(game))
                    {
                        _logger.log_action("- Giocatore "+ std::to_string(winner_index(game))+" ha vinto la partita ");
                        game->board()->state(GameState::Ended);
                        return GameInfo(*game, _logger);
                    }

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
                    _logger.log_action("- Giocatore "+ std::to_string(player_index)+" ha pagato "+ std::to_string(payment)+" al giocatore "+ std::to_string(tile.owner_id())+ " per pernottamento nella casella "+ std::to_string(new_position));
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
        throw std::exception();
    }

    return GameInfo(*game, _logger );
}

GameInfo process_player_payment(GameData* game, ActionInfo action)
{   
    GameLogger _logger;

    auto player_index = game->board()->player_turns().get_current_player_index();
    

    if (action.type() != ActionType::AcceptPayment && action.type() != ActionType::DenyPayment)
    {
        throw std::exception();
    }

    //std::cout << "Processing payment...\n";

    if (action.type() == ActionType::DenyPayment)
    {
        //std::cout << "Player " << game->board()->player_turns().at(game->board()->round() % game->board()->get_player_number()) << " denied the payment.\n";
        game->board()->next_round();
        game->board()->state(GameState::PlayerDiceThrow);
        return GameInfo(*game, _logger);
    }

    
    auto player_position = game->board()->player(player_index)->position();

    auto tile = game->board()->tile(player_position);

    switch (tile.housing())
    {
        case TileHousing::Land:
        {
            if (tile.owner_id() == player_index)
            {
                auto payment = game->configuration().get_prize(PaymentAction::BuyHouse, tile.category());
                game->board()->player(player_index)->debit(payment);

                game->board()->tile(player_position).housing(TileHousing::House);

                //std::cout << "Player " << player_index << " upgraded to an house and has now " << game->board()->player(player_index)->coins() << " coins.\n";

                _logger.log_action("- Giocatore "+ std::to_string(player_index)+ " ha costruito una casa sul terreno "+ std::to_string(player_position));

            } else {
                auto payment = game->configuration().get_prize(PaymentAction::BuyLand, tile.category());
                game->board()->player(player_index)->debit(payment);
                
                game->board()->tile(player_position).set_property(player_index);

                //std::cout << "Player " << player_index << " bought a land and has now " << game->board()->player(player_index)->coins() << " coins.\n";

                _logger.log_action("- Giocatore "+ std::to_string(player_index)+ " ha acquistato il terreno "+ std::to_string(player_position));
                
            }
            break;
        }
        case TileHousing::House:
        {   
            auto payment = game->configuration().get_prize(PaymentAction::BuyHotel, tile.category());
            game->board()->player(player_index)->debit(payment);

            game->board()->tile(player_position).housing(TileHousing::Hotel);

            //std::cout << "Player " << player_index << " upgraded to an hotel and has now " << game->board()->player(player_index)->coins() << " coins.\n";

            _logger.log_action("- Giocatore "+ std::to_string(player_index)+ " ha migliorato una casa in albergo sul terreno "+ std::to_string(player_position));
                
            break;
        }
        default:
            throw std::exception();
            break;
    }

    game->board()->tile(player_position).set_property(player_index);

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

    throw std::exception();
}

object_models::GameInfo engine::GameProcessor::init_game(object_models::GameData* game)
{
    int playerNumber = game->configuration().player_number();

    std::map<int, int> pointsByPlayer;

    for (int i = 0; i < playerNumber; i++)
    {
        pointsByPlayer[i] = _random->get_next(1, 6) + _random->get_next(1, 6);
    }

    std::vector<int> keys = find_keys(pointsByPlayer);
    
    do
    {
        for (int i = 0; i < keys.size(); i++)
        {
            pointsByPlayer[keys[i]] = _random->get_next(1, 6) + _random->get_next(1, 6);
        }

        keys = find_keys(pointsByPlayer);

    } while (keys.size() > 0);

    std::vector<int> sortedPlayers = get_keys(pointsByPlayer);

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