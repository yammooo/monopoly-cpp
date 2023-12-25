#ifndef ACTION_INFO_H
#define ACTION_INFO_H

#include "ActionType.h"
#include "PaymentAction.h"

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