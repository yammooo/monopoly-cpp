#include "../../include/ObjectModels/Player.h"

bool object_models::Player::is_valid()
{
    return _id >= 0 && _boardPosition >= 0;
}