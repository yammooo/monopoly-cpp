#include "../../include/Engine/GameRepository.h"

using namespace object_models;

void engine::GameRepository::save_game(GameData game)
{
    _games[game.id()] = game;
}

GameData engine::GameRepository::get_game(int id)
{
    return _games[id];
}