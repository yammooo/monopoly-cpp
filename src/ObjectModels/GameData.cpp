// Author: Gianmaria Frigo

#include <exception>
#include <ostream>

#include "../../include/ObjectModels/GameData.h"
#include "../../include/ObjectModels/Tile.h"

using namespace object_models;

GameData::GameData(int id, GameConfiguration configuration)
{
    _id = id;
    _configuration = configuration;
    
    std::vector<PlayerData> players;

    for (int i = 0; i < configuration.player_number(); i++)
    {
        // Create a new player with the index as the player's ID, positioned at the start tile,
        // and with the initial balance specified in the configuration
        players.push_back(PlayerData(i, 0, configuration.initial_balance()));
    }

    _board = GameBoard(configuration.tiles(), players);
}

std::string object_models::GameData::board_to_string()
{
    const int board_size = _configuration.board_size()/4 + 1;

    // Matrix representing the board
    std::vector<std::vector<std::string>> board_matrix(board_size, std::vector<std::string>(board_size));

    int vector_index = 0;

    // Fill last row excluding last column
    for (int column = board_size - 1; column > 0; column--)
    {
        int row = board_size - 1;
        board_matrix[row][column] = tile_to_string(_board.tile(vector_index), vector_index);
        vector_index++;
    }

    // Fill first column excluding last row
    for (int row = board_size - 1; row > 0; row--)
    {
        int column = 0;
        board_matrix[row][column] = tile_to_string(_board.tile(vector_index), vector_index);
        vector_index++;
    }

    // Fill first row excluding first column
    for (int column = 0; column < board_size - 1; column++)
    {
        int row = 0;
        board_matrix[row][column] = tile_to_string(_board.tile(vector_index), vector_index);
        vector_index++;
    }

    // Fill last column excluding first row
    for (int row = 0; row < board_size - 1; row++)
    {
        int column = board_size - 1;
        board_matrix[row][column] = tile_to_string(_board.tile(vector_index), vector_index);
        vector_index++;
    }

    // Fill center
    for (int row = 1; row < board_size - 2; row++)
    {
        for (int column = 1; column < board_size - 2; column++)
        {
            board_matrix[row][column] = "";
        }
    }

    std::string output;

    for (int row = -1; row < board_size; row++)
    {   
        // If the row index is -1, it means we are at the row used for column headers (1, 2, 3, ...)
        if (row == -1)
        {   
            output.append("\t");
            for (int column = 0; column < board_size; column++)
            {
                output.append(std::to_string(column + 1));
                output.append("\t");
            }
            output.append("\n");
        }
        else
        {
            for (int column = -1; column < board_size; column++)
            {
                // If the column index is -1, it means we are at the column used for row headers (A, B, C, ...)
                if (column == -1)
                {   
                    output.append(1,('A' + row));
                    output.append("\t");
                }
                else
                {
                    output.append(board_matrix[row][column]);
                    output.append("\t");
                }
            }
            output.append("\n");
        }
    }

    return output;
}

std::string object_models::GameData::players_properties_to_string()
{
    std::string output;

    for (int player_number = 0; player_number < _board.get_player_number(); player_number++)
    {
        output.append("Giocatore ");
        output.append(std::to_string(player_number + 1));
        output.append(": ");

        int property_count = 0;

        // Loop over each tile on the game board to find the ones owned by the current player
        for (int tile_number = 0; tile_number < _board.board_size(); tile_number++)
        {
            if (_board.tile(tile_number).owner_id() == player_number)
            {
                output.append(_board.tile(tile_number).name());
                output.append(", ");
                property_count++;
            }
        }

        output.append(property_count > 0 ? "\b\b \n" : "\n");
    }

    return output;
}

std::string object_models::GameData::players_coins_to_string()
{
    std::string output;

    for (int player_number = 0; player_number < _board.get_player_number(); player_number++)
    {
        int player_coins = _board.player(player_number)->coins();

        output.append("Giocatore ");
        output.append(std::to_string(player_number + 1));
        output.append(": ");

        if(player_coins >= 0)
        {
            output.append(std::to_string(_board.player(player_number)->coins()));
        }

        output.append("\n");
    }

    return output;
}

std::vector<int> object_models::GameData::players_coins_to_vector()
{
    std::vector<int> playerCoins;

    for (int player_number = 0; player_number < _board.get_player_number(); player_number++)
    {
        int player_coins = _board.player(player_number)->coins();
        playerCoins.push_back(player_coins);
    }

    return playerCoins;
}

std::string object_models::GameData::tile_to_string(Tile tile, int tile_index)
{
    std::string output;

    output.append("| ");

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



    for (int i=0; i<_board.get_player_number(); i++)
    {
        if ((_board.player(i)->position() == tile_index) && (_board.player(i)->is_in_game()))
        {
            output.append(std::to_string(i + 1));
        }
    }

    output.append(" |");

    return output;
}