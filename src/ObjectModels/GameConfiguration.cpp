// Author: Gianmaria Frigo

#include <random>
#include <algorithm>
#include <stdexcept>
#include <string>

#include "../../include/ObjectModels/GameConfiguration.h"

using namespace object_models;
using namespace std;

std::string tile_index_to_name(int index, int dimension);

GameConfiguration GameConfiguration::_default = GameConfiguration(
	8,      // Cheap tiles
	10,     // Standard tiles
	6,      // Luxury tiles
	
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

	100,    // Max round
	100,    // Initial balance
	20,     // Start prize
	4       // Player number
);

GameConfiguration GameConfiguration::get_default()
{
	return _default;
}

GameConfiguration::GameConfiguration(vector<Tile> tiles, map<PaymentAction, map<TileCategory, int>> prices, int maxRound, int initialBalance, int startPrize, int playerNumber)
    : _tiles{tiles},
    _prices{prices},
    _maxRound{maxRound},
    _initialBalance{initialBalance},
    _startPrize{startPrize},
    _playerNumber{playerNumber}
{
}

GameConfiguration::GameConfiguration(int cheapTilesNumber, int standardTilesNumber, int luxuryTilesNumber, std::map<object_models::PaymentAction, std::map<object_models::TileCategory, int>> prices, int maxRound, int initialBalance, int startPrize, int playerNumber)
    : _prices(prices),
    _maxRound(maxRound),
    _initialBalance(initialBalance),
    _startPrize(startPrize),
    _playerNumber(playerNumber)
{	
    // Checks if the total number of tiles forms a square board
	if ((cheapTilesNumber + standardTilesNumber + luxuryTilesNumber + 4) % 4 != 0)
	{
		throw std::invalid_argument("The game configuration is invalid. The board must be a square.");
	}

	std::random_device device;
    std::mt19937 rng(device());

	int total_tile_size = cheapTilesNumber + standardTilesNumber + luxuryTilesNumber + 4;

    // Create the cheap tiles
    for (int i = 0; i < cheapTilesNumber; i++)
	{
		_tiles.push_back(Tile(TileCategory::Cheap, TileHousing::Land));
	}

    // Create the standard tile
    for (int i = 0; i < standardTilesNumber; i++)
	{
		_tiles.push_back(Tile(TileCategory::Standard, TileHousing::Land));
	}

    // Create the luxury tiles
    for (int i = 0; i < luxuryTilesNumber; i++)
	{
		_tiles.push_back(Tile(TileCategory::Luxury, TileHousing::Land));
	}

    // Shuffle the tiles to randomize their order
	std::shuffle(_tiles.begin(), _tiles.end(), rng);

    // Insert the corner tiles at the correct positions
	_tiles.insert(_tiles.begin(), Tile(TileCategory::Start, TileHousing::Undefined));
    _tiles.insert(_tiles.begin() + total_tile_size / 4, Tile(TileCategory::Corner, TileHousing::Undefined));
    _tiles.insert(_tiles.begin() + total_tile_size / 2, Tile(TileCategory::Corner, TileHousing::Undefined));
    _tiles.insert(_tiles.begin() + 3 * total_tile_size / 4, Tile(TileCategory::Corner, TileHousing::Undefined));

    // Assign the correct position and name to each tile
	for (int i = 0; i < _tiles.size(); i++)
	{	
		_tiles[i].position(i);
		_tiles[i].name(tile_index_to_name(i, (total_tile_size/4)+1));
	}

}

// Function to convert a tile index to a name based on its position on the board
std::string tile_index_to_name(int index, int dimension) {
    
    // Dimension is the length of the side of the board
    
    // Determine which side of the board the tile is on
    int part_of_vector = index/(dimension-1);

    // Determine the position of the tile on that side
    int pos_of_part = index%(dimension-1);
    
    char row;
    int column;
    std::string output="";
    
    switch(part_of_vector)
    {
        case 0:                           // South side (H2 to H8 on an 8x8 board)
            row = 'A' + (dimension-1);
            output.append(1,row) ;

            column = dimension - pos_of_part;
            output.append(std::to_string(column)) ;

            
            break;

        case 1:                          // West side (B1 to H1 on an 8x8 board)
            row = 'A'+ (dimension -1 -(pos_of_part));
            output.append(1,row) ;

            column = 1;
            output.append(std::to_string(column)) ;

            break;


        case 2:                         // North side (A1 to A7 on an 8x8 board)
            row = 'A';
            output.append(1,row) ;

            column= pos_of_part +1 ;
            output.append(std::to_string(column)) ;
            
            break;

        case 3:                         // East side (e.g., A8 to G8 on an 8x8 board)
            row = 'A' +(pos_of_part);
            output.append(1, row) ;

            column = dimension;
            output.append(std::to_string(column));
            
            break;
    }
    
    return output;
}