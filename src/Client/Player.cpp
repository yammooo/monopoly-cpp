#include "../../include/Client/Player.h"

using namespace object_models;
using namespace client;
using namespace object_states;

ActionInfo Player::get_action(GameInfo info)
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
            std::string result; // INPUT
            cin>>result;

			if (result[0]=="N")
			{
				return ActionInfo(ActionType::DenyPayment);
			}
			else
			{
				return ActionInfo(ActionType::AcceptPayment); // perche se non è ne si ne no accetta 
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