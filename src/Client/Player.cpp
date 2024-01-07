#include <iostream>

#include "../../include/Client/Player.h"

using namespace std;
using namespace object_models;
using namespace client;
using namespace object_states;

ActionInfo Player::get_action(GameInfo info)
{
	GameState state = info.state();

    if (state == GameState::PlayerDiceThrow)
    {
        return ActionInfo(ActionType::ThrowDice);
    }
	else if ((state == GameState::PlayerBuyLand) || (state == GameState::PlayerBuyHouse) || (state == GameState::PlayerBuyHotel))
	{
		int player_index = info.player_turns().get_current_player_index();

		if (state == GameState::PlayerBuyLand)
		{
			cout << "- Giocatore " << player_index << ": Vuoi comprare il terreno? (S/N)" << endl;
		}
		else if (state == GameState::PlayerBuyHouse)
		{
			cout << "- Giocatore " << player_index << ": Vuoi comprare la casa? (S/N)" << endl;
		}
		else if (state == GameState::PlayerBuyHotel)
		{
			cout << "- Giocatore " << player_index << ": Vuoi comprare l'hotel? (S/N)" << endl;
		}

		string answer;
		cin >> answer;

		bool is_yes = answer == "S";

		if (is_yes)
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