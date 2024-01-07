#include "../../include/ObjectModels/GameBoard.h"

using namespace object_models;
using namespace object_states;

GameBoard::GameBoard(const std::vector<Tile>& tiles, const std::vector<PlayerData>& players)
{
    _roundCount = 0;
    _state = GameState::PlayerDiceThrow;

    _tiles = tiles;
    _players = players;
}

int object_models::GameBoard::winner()
{
    if (_state != GameState::Ended)
    {
        return -1;
    }

    int index = -1;

    for (auto player : _players)
    {
        if (player.coins() > 0)
        {
            index = player.id();
            break;
        }
    }

    return index;
}