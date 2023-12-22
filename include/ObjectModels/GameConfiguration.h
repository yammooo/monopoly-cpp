#ifndef GAME_CONFIGURATION_H
#define GAME_CONFIGURATION_H

#include <vector>
#include <map>
#include "Tile.h"
#include "PaymentAction.h"

namespace object_models
{
    class GameConfiguration
    {
        private:

        static GameConfiguration _default;

        std::vector<object_models::Tile> _tiles;
        std::map<object_models::PaymentAction, std::map<object_models::TileCategory, int>> _prices;

        int _maxRound;
        int _initialBalance;
        int _startPrize;
        int _playerNumber;
        
        public:

        static GameConfiguration get_default();

        std::vector<object_models::Tile> tiles() { return _tiles; }; 
        std::map<object_models::PaymentAction, std::map<object_models::TileCategory, int>> prices() { return _prices; }

        int maxRound() { return _maxRound; }
        int initialBalance() { return _initialBalance; }
        int startPrize() { return _startPrize; }
        int playerNumber() { return _playerNumber; }

        GameConfiguration() {}

        GameConfiguration(std::vector<object_models::Tile> tiles, 
                          std::map<object_models::PaymentAction, std::map<object_models::TileCategory, int>> prices,
                          int maxRound,
                          int initialBalance,
                          int startPrize,
                          int playerNumber);

    };
}

#endif // GAME_CONFIGURATION_H