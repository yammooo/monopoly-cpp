#include "../include/Client/Bot.h"

using namespace object_models;
using namespace client;
using namespace object_states;

ActionInfo Bot::get_action(GameInfo info)
{
	GameState state = info.state();

    if (state == GameState::PlayerDiceThrow)
    {
        return ActionInfo(ActionType::ThrowDice);
    }
	else if ((state == GameState::PlayerBuyLand) || (state == GameState::PlayerBuyHouse) || (state == GameState::PlayerBuyHotel))
	{
		int result = _random->get_next(1, 100);

		if (result <= 25)
		{
			return ActionInfo(ActionType::AcceptPayment);
		}
		else
		{
			return ActionInfo(ActionType::DenyPayment);
		}
    }

    throw std::exception();
}