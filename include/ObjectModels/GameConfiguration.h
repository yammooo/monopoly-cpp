// Author: Gianmaria Frigo

#ifndef GAME_CONFIGURATION_H
#define GAME_CONFIGURATION_H

#include <vector>
#include <map>

#include "Tile.h"
#include "PaymentAction.h"
#include "../DependencyInjection/ServiceProvider.h"

namespace object_models
{   
    // The GameConfiguration class represents the configuration of a game.
    // It includes information about the game tiles, prices, maximum rounds, initial balance, start prize, and number of players.
    class GameConfiguration
    {
        private:

            // Default configuration for the game
            static GameConfiguration _default;

            std::vector<object_models::Tile> _tiles;

            // Map of the price of any action for any category of tile.
            std::map<object_models::PaymentAction, std::map<object_models::TileCategory, int>> _prices;

            int _maxRound;
            int _initialBalance;
            int _startPrize;
            int _playerNumber;
            
        public:

            static GameConfiguration get_default();

            std::vector<object_models::Tile> tiles() { return _tiles; }; 
            std::map<object_models::PaymentAction, std::map<object_models::TileCategory, int>> prices() { return _prices; }

            int max_round() const { return _maxRound; }
            int initial_balance() const { return _initialBalance; }
            int start_prize() const { return _startPrize; }
            int player_number() const { return _playerNumber; }
            int board_size() const { return _tiles.size(); }
            int get_prize(object_models::PaymentAction action, object_models::TileCategory category) const { return _prices.at(action).at(category); }

            GameConfiguration() {}

            GameConfiguration(std::vector<object_models::Tile> tiles,
                            std::map<object_models::PaymentAction, std::map<object_models::TileCategory, int>> prices,
                            int maxRound,
                            int initialBalance,
                            int startPrize,
                            int playerNumber);

            GameConfiguration(int cheapTilesNumber,
                            int standardTilesNumber,
                            int luxuryTilesNumber,
                            std::map<object_models::PaymentAction, std::map<object_models::TileCategory, int>> prices,
                            int maxRound,
                            int initialBalance,
                            int startPrize,
                            int playerNumber);
    };
}

#endif // GAME_CONFIGURATION_H