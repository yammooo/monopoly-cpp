#include "../../include/ObjectModels/GameConfiguration.h"

using namespace object_models;
using namespace std;

GameConfiguration GameConfiguration::_default = GameConfiguration(
  vector<Tile> {

    Tile(TileCategory::Start, TileHousing::Undefined),

    Tile(TileCategory::Cheap, TileHousing::Land),
    Tile(TileCategory::Cheap, TileHousing::Land),
    Tile(TileCategory::Standard, TileHousing::Land),
    Tile(TileCategory::Luxury, TileHousing::Land),
    Tile(TileCategory::Standard, TileHousing::Land),
    Tile(TileCategory::Standard, TileHousing::Land),

    Tile(TileCategory::Corner, TileHousing::Undefined),
    
    Tile(TileCategory::Cheap, TileHousing::Land),
    Tile(TileCategory::Cheap, TileHousing::Land),
    Tile(TileCategory::Standard, TileHousing::Land),
    Tile(TileCategory::Luxury, TileHousing::Land),
    Tile(TileCategory::Standard, TileHousing::Land),
    Tile(TileCategory::Luxury, TileHousing::Land),

    Tile(TileCategory::Corner, TileHousing::Undefined),

    Tile(TileCategory::Luxury, TileHousing::Land),
    Tile(TileCategory::Luxury, TileHousing::Land),
    Tile(TileCategory::Cheap, TileHousing::Land),
    Tile(TileCategory::Standard, TileHousing::Land),
    Tile(TileCategory::Standard, TileHousing::Land),
    Tile(TileCategory::Standard, TileHousing::Land),

    Tile(TileCategory::Corner, TileHousing::Undefined),

    Tile(TileCategory::Standard, TileHousing::Land),
    Tile(TileCategory::Cheap, TileHousing::Land),
    Tile(TileCategory::Standard, TileHousing::Land),
    Tile(TileCategory::Cheap, TileHousing::Land),
    Tile(TileCategory::Luxury, TileHousing::Land),
    Tile(TileCategory::Cheap, TileHousing::Land),
  },

  // Create the payment action map
  map<PaymentAction, map<TileCategory, int>> {
    { PaymentAction::BuyLand, map<TileCategory, int> {
      { TileCategory::Cheap, 6 },
      { TileCategory::Standard, 10 },
      { TileCategory::Luxury, 20 }
    }},
    { PaymentAction::BuyHouse, map<TileCategory, int> {
      { TileCategory::Cheap, 3 },
      { TileCategory::Standard, 5 },
      { TileCategory::Luxury, 10 }
    }},
    { PaymentAction::BuyHotel, map<TileCategory, int> {
      { TileCategory::Cheap, 3 },
      { TileCategory::Standard, 5 },
      { TileCategory::Luxury, 10 }
    }},
    { PaymentAction::HouseStay, map<TileCategory, int> {
      { TileCategory::Cheap, 2 },
      { TileCategory::Standard, 4 },
      { TileCategory::Luxury, 7 }
    }},
    { PaymentAction::HotelStay, map<TileCategory, int> {
      { TileCategory::Cheap, 4 },
      { TileCategory::Standard, 8 },
      { TileCategory::Luxury, 14 }
    }}
  },
  100,
  100,
  20,
  4
);

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