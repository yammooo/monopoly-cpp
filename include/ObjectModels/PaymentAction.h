#ifndef PAYMENT_ACTION_H
#define PAYMENT_ACTION_H

namespace object_models
{
    enum class PaymentAction
    {
        Undefined = 0,
        BuyLand = 1,
        BuyHouse = 2,
        BuyHotel = 3,
        HouseStay = 4,
        HotelStay = 5
    };
}

#endif // PAYMENT_ACTION_H