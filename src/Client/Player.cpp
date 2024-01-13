// Author: Martina Naldoni

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
		string answer;

		do
		{
			if (state == GameState::PlayerBuyLand)
			{
				cout << "- Giocatore " << player_index + 1 << ": Vuoi comprare il terreno? (S/N/show)" << endl;
			}
			else if (state == GameState::PlayerBuyHouse)
			{
				cout << "- Giocatore " << player_index + 1 << ": Vuoi comprare la casa? (S/N/show)" << endl;
			}
			else if (state == GameState::PlayerBuyHotel)
			{
				cout << "- Giocatore " << player_index + 1 << ": Vuoi comprare l'hotel? (S/N/show)" << endl;
			}

			cin >> answer;

			if (answer == "S")
			{
				return ActionInfo(ActionType::AcceptPayment);
			}
			else if (answer == "N")
			{
				return ActionInfo(ActionType::DenyPayment);
			}
			else if (answer == "show")
			{	
				cout << endl << "Tabellone:" << endl;
				cout << info.board_string() << endl;

				cout << "Proprietà possedute dai giocatori:" << endl;
				cout << info.players_properties_string() << endl;

				cout << "Fiorini posseduti dai giocatori:" << endl;
				cout << info.players_coins_string() << endl;
			}

		} while (answer != "S" && answer != "N");

    }

    throw std::exception();
}