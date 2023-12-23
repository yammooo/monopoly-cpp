#include "../../include/ObjectModels/Player.h"

object_models::Player::Player(int id, int position, int coins)
{
    _id = id;
    _position = position;
    _coins = coins;
}

bool object_models::Player::is_valid()
{
    return _id >= 0 && _position >= 0;
}

void object_models::Player::debit(int coins)
{
    // TODO: Create exceptions
    if (coins < 0)
    {
        throw "error";
    }

    _coins -= coins;
}

void object_models::Player::credit(int coins)
{
    // TODO: Create exceptions
    if (coins < 0)
    {
        throw "error";
    }

    _coins -= coins;
}