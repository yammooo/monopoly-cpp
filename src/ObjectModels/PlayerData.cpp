#include <stdexcept>

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
    if (coins < 0)
    {
        throw std::invalid_argument("Number of coins to debit cannot be negative");
    }

    _coins -= coins;
}

void object_models::PlayerData::credit(int coins)
{
    if (coins < 0)
    {
        throw std::invalid_argument("Number of coins to credit cannot be negative");
    }

    _coins += coins;
}