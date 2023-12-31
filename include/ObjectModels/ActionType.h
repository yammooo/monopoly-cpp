// Author: Martina Naldoni

#ifndef ACTION_TYPE_H
#define ACTION_TYPE_H

namespace object_models
{
    enum class ActionType
    {
        Undefined = 0,
        ThrowDice = 2,
        AcceptPayment = 3,
        DenyPayment = 4
    };
}

#endif // ACTION_TYPE_H