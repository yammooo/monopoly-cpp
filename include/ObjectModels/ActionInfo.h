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
        int _otherPlayerId;
        
        public:

        ActionInfo(ActionType type, PaymentAction paymentAction, int playerId, int otherPlayerId);

        ActionType type() const { return _type; }
        PaymentAction payment_action() const { return _paymentAction; }
        int player_id() const { return _playerId; }
        int other_player_id() const { return _otherPlayerId; }
        
    };
}

#endif // ACTION_INFO_H