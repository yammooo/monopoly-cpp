#include "../../include/ObjectModels/GameConfiguration.h"

using namespace object_models;
using namespace std;

GameConfiguration GameConfiguration::_default = GameConfiguration(vector<Tile> {
                                                                    Tile(),
                                                                    Tile(),
                                                                    Tile()
                                                                  },
                                                                  map<PaymentAction, map<TileCategory, int>> {
                                                                    { PaymentAction::BuyHotel, map<TileCategory, int> {
                                                                        { TileCategory::Start, 10 }
                                                                    }}
                                                                  },
                                                                  1000,
                                                                  100,
                                                                  20, 
                                                                  4);

GameConfiguration GameConfiguration::get_default()
{
	return _default;
}

GameConfiguration::GameConfiguration(vector<Tile> tiles, map<PaymentAction, map<TileCategory, int>> prices, int maxRound, int initialBalance, int startPrize, int playerNumber)
{
    _tiles = tiles;
    _prices = prices;
    _maxRound = maxRound;
    _initialBalance = initialBalance;
    _startPrize = startPrize;
    _playerNumber = playerNumber;
}