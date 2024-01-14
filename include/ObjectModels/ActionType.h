// Author: Martina Naldoni

#ifndef ACTION_TYPE_H
#define ACTION_TYPE_H

namespace object_models
{
    enum class ActionType
    {
        Undefined = 0,
        ThrowDice = 1,
        AcceptPayment = 2,
        DenyPayment = 3
    };
}

#endif // ACTION_TYPE_H