#include <exception>
#include <ostream>

#include "../../include/ObjectModels/GameData.h"
#include "../../include/ObjectModels/Tile.h"

using namespace object_models;

std::string tile_to_string(Tile tile);

GameData::GameData(int id, GameConfiguration configuration)
{
    _id = id;
    _configuration = configuration;
    
    std::vector<PlayerData> players;

    for (int i = 0; i < configuration.player_number(); i++)
    {
        players.push_back(PlayerData(i, 0, configuration.initial_balance()));
    }

    _board = GameBoard(configuration.tiles(), players);

    // TODO: Add board configured as configuration says :)
}

std::string object_models::GameData::board_to_string()
{
    const int board_size = _configuration.board_size()/4 + 1;

    std::vector<std::vector<std::string>> board_matrix(board_size, std::vector<std::string>(board_size));

    int vector_index = 0;

    // fill last row excluding last column
    for (int column = board_size - 1; column > 0; column--)
    {
        int row = board_size - 1;
        board_matrix[row][column] = tile_to_string(_board.tile(vector_index++));
    }

    // fill first column excluding last row
    for (int row = board_size - 1; row > 0; row--)
    {
        int column = 0;
        board_matrix[row][column] = tile_to_string(_board.tile(vector_index++));
    }

    // fill first row excluding first column
    for (int column = 0; column < board_size - 1; column++)
    {
        int row = 0;
        board_matrix[row][column] = tile_to_string(_board.tile(vector_index++));
    }

    // fill last column excluding first row
    for (int row = 0; row < board_size - 1; row++)
    {
        int column = board_size - 1;
        board_matrix[row][column] = tile_to_string(_board.tile(vector_index++));
    }

    // fill center
    for (int row = 1; row < board_size - 2; row++)
    {
        for (int column = 1; column < board_size - 2; column++)
        {
            board_matrix[row][column] = "";
        }
    }

    std::string output;

    for (int row = 0; row < board_size; row++)
    {
        for (int column = 0; column < board_size; column++)
        {
            output.append("| ");
            output.append(board_matrix[row][column]);
            output.append(" |");
            output.append("\t");
        }
        output.append("\n");
    }

    return output;
}

std::string tile_to_string(Tile tile)
{
    std::string output;

    switch (tile.category())
    {
        case TileCategory::Cheap:
            output.append("E");
            break;
        case TileCategory::Standard:
            output.append("S");
            break;
        case TileCategory::Luxury:
            output.append("L");
            break;
        case TileCategory::Start:
            output.append("P");
            break;
        case TileCategory::Corner:
            output.append(" ");
            break;
        default:
            throw std::invalid_argument("Invalid tile category");
    }

    switch (tile.housing())
    {
        case TileHousing::Land:
            break;
        case TileHousing::House:
            output.append("*");
            break;
        case TileHousing::Hotel:
            output.append("^");
            break;
        default:
            break;
    }

    int owner_id = tile.owner_id();

    if (owner_id != -1)
    {
        output.append(std::to_string(owner_id));
    }

    return output;
}