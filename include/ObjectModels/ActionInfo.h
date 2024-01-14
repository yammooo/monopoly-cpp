// Author: Martina Naldoni

#ifndef ACTION_INFO_H
#define ACTION_INFO_H

#include "ActionType.h"
#include "PaymentAction.h"

/*
We decided to divide the actions in two types : ActionType and PaymentAction.
The possible values they can assume all have a meaning that is described
in 'ActionType.h' and 'Paymentaction.h'

This class provides a unified way to handle different types of actions in the game logic.
*/

namespace object_models
{
    class ActionInfo
    {
        private:

        ActionType _type;
        PaymentAction _paymentAction;
        
        public:

        ActionInfo() { }
        ActionInfo(ActionType type);
        ActionInfo(ActionType type, PaymentAction paymentAction);

        ActionType type() const { return _type; }
        PaymentAction payment_action() const { return _paymentAction; }
    };
}

#endif // ACTION_INFO_H