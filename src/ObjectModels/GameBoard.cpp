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