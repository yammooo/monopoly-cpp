#include "../../include/ObjectModels/ActionInfo.h"

object_models::ActionInfo::ActionInfo(ActionType type, PaymentAction paymentAction, int playerId)
    : _type(type), _paymentAction(paymentAction), _playerId(playerId) {}