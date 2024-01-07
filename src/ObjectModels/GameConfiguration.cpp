#include <random>
#include <algorithm>
#include <stdexcept>

#include "../../include/ObjectModels/GameConfiguration.h"

using namespace object_models;
using namespace std;

GameConfiguration GameConfiguration::_default = GameConfiguration(
	8,
	10,
	6,
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
	2,
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

GameConfiguration::GameConfiguration(int cheapTilesNumber,
                                    int standardTilesNumber,
                                    int luxuryTilesNumber,
                                    std::map<object_models::PaymentAction, std::map<object_models::TileCategory, int>> prices,
                                    int maxRound,
                                    int initialBalance,
                                    int startPrize,
                                    int playerNumber
                                    )
{	
	if ((cheapTilesNumber + standardTilesNumber + luxuryTilesNumber + 4) % 4 != 0)
	{
		throw std::invalid_argument("The game configuration is invalid. The board must be a square.");
	}
	
    _prices = prices;
    _maxRound = maxRound;
    _initialBalance = initialBalance;
    _startPrize = startPrize;
    _playerNumber = playerNumber;

	std::random_device device;
    std::mt19937 rng(device());

	int tile_size = cheapTilesNumber + standardTilesNumber + luxuryTilesNumber + 4;

    for (int i = 0; i < cheapTilesNumber; i++)
	{
		_tiles.push_back(Tile(TileCategory::Cheap, TileHousing::Land));
	}

    for (int i = 0; i < standardTilesNumber; i++)
	{
		_tiles.push_back(Tile(TileCategory::Standard, TileHousing::Land));
	}

    for (int i = 0; i < luxuryTilesNumber; i++)
	{
		_tiles.push_back(Tile(TileCategory::Luxury, TileHousing::Land));
	}

	std::shuffle(_tiles.begin(), _tiles.end(), rng);

	_tiles.insert(_tiles.begin(), Tile(TileCategory::Start, TileHousing::Undefined));
    _tiles.insert(_tiles.begin() + tile_size / 4, Tile(TileCategory::Corner, TileHousing::Undefined));
    _tiles.insert(_tiles.begin() + tile_size / 2, Tile(TileCategory::Corner, TileHousing::Undefined));
    _tiles.insert(_tiles.begin() + 3 * tile_size / 4, Tile(TileCategory::Corner, TileHousing::Undefined));
}