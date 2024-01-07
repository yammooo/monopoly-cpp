#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include <queue>
#include <vector>

namespace object_models
{
	class TurnManager
	{
		private:

		std::queue<int> _playerTurns;

		public:

		TurnManager(std::vector<int> turns);

		void remove_player(int player_index);

		int get_next_player_index();

		int get_current_player_index();
	};
}

#endif