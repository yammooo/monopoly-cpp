#include "../../include/ObjectModels/GameInfo.h"

object_models::GameInfo::GameInfo(int id)
{
    _id = id;
}

object_models::GameInfo::GameInfo(object_models::GameData game, engine::GameLogger logger)
{
    _id = game.id();
    _playerNumber = game.board()->get_player_number();
    _state = game.board()->state();
    _round = game.board()->round();
    _playerTurns = game.board()->player_turns();
    _winner = game.board()->winner();
    _logger = logger;
    _board_string = game.board_to_string();
    _players_properties_string = game.players_properties_to_string();
    _players_coins_string = game.players_coins_to_string();
}


object_models::GameInfo::GameInfo(object_models::GameData game){
    
    _id = game.id();
    _playerNumber = game.board()->get_player_number();
    _state = game.board()->state();
    _round = game.board()->round();
    _playerTurns = game.board()->player_turns();
    _winner = game.board()->winner();
    _board_string = game.board_to_string();
    _players_properties_string = game.players_properties_to_string();
}
