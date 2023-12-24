#ifndef ACTION_TYPE_H
#define ACTION_TYPE_H

namespace object_models
{
    enum class ActionType
    {
        Undefined = 0,
        PassedStart = 1,
        DiceRoll = 2,
        LandedOn = 3,
        Payment = 4,
        EndedTurn = 5,
        Eliminated = 6,
        Won = 7
    };
}

#endif // ACTION_TYPE_H