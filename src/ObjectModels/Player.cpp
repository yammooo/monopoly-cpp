#include "../../include/ObjectModels/Player.h"

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