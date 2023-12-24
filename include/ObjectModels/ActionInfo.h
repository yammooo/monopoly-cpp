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
        int _playerId;
        
        public:

        ActionInfo() { }
        ActionInfo(ActionType type, PaymentAction paymentAction, int playerId);

        ActionType type() const { return _type; }
        PaymentAction payment_action() const { return _paymentAction; }
        int player_id() const { return _playerId; }        
    };
}

#endif // ACTION_INFO_H