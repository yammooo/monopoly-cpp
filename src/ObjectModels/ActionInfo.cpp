#include "../../include/ObjectModels/ActionInfo.h"

object_models::ActionInfo::ActionInfo(ActionType type, PaymentAction paymentAction, int playerId, int otherPlayerId)
    : _type(type), _paymentAction(paymentAction), _playerId(playerId), _otherPlayerId(otherPlayerId) {}