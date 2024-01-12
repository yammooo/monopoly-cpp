// Author: Martina Naldoni

#include "../../include/ObjectModels/ActionInfo.h"

object_models::ActionInfo::ActionInfo(ActionType type, PaymentAction paymentAction)
    : _type(type), _paymentAction(paymentAction) {}

object_models::ActionInfo::ActionInfo(ActionType type)
    : _type(type) {}