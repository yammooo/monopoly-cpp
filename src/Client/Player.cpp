#include "../include/Client/Player.h"

using namespace object_models;
using namespace client;
using namespace object_states;

ActionInfo Player::get_action(GameInfo info)
{
	switch (info.state())
	{
		case GameState::PlayerDiceThrow:
		{   
            //ask for a show
			return ActionInfo(ActionType::ThrowDice);
			break;
		}
		case GameState::PlayerPayment:
		{
			//chiedo se vuole comprare  E se vuole uno show
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
        /*case GameState::PlayerRequest: 
        {
            // vuole vedere la board
            // vuole vedere lista terreni case posseduti 
            // vuole vedere il saldo di tutti 
            return ActionInfo(ActionType::ShowToPlayer);

        }*/
		default:
		{
			throw std::exception();
			break;
		}
	}
}