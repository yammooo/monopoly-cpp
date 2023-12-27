#include "../include/Client/Bot.h"

using namespace object_models;
using namespace client;
using namespace object_states;

ActionInfo Bot::get_action(GameInfo info)
{
	switch (info.state())
	{
		case GameState::PlayerDiceThrow:
		{
			return ActionInfo(ActionType::ThrowDice);
			break;
		}
		case GameState::PlayerPayment:
		{
			auto result = _random->get_next(1, 100);

			if (result <= 100)
			{
				return ActionInfo(ActionType::AcceptPayment);
			}
			else
			{
				return ActionInfo(ActionType::DenyPayment);
			}

			break;
		}
		default:
		{
			throw std::exception();
			break;
		}
	}
}