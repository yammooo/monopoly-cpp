#include "../../include/ObjectModels/PlayerData.h"

object_models::PlayerData::PlayerData(int id, int position, int coins)
{
    _id = id;
    _position = position;
    _coins = coins;
}

bool object_models::PlayerData::is_valid()
{
    return _id >= 0 && _position >= 0;
}

void object_models::PlayerData::debit(int coins)
{
    // TODO: Create exceptions
    if (coins < 0)
    {
        throw "error";
    }

    _coins -= coins;
}

void object_models::PlayerData::credit(int coins)
{
    // TODO: Create exceptions
    if (coins < 0)
    {
        throw "error";
    }

    _coins += coins;
}