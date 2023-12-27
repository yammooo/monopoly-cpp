#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include <vector>
#include <queue>

namespace object_models
{
	class TurnManager
	{
		private:

		std::queue<int> _playerTurns;

		public:

		TurnManager(std::vector<int> turns)
		{
			_playerTurns = std::queue<int>();

			for (auto turn in turns)
			{
				_playerTurns.push(turn);
			}
		}

		void remove_player(int player_index)
		{
			std::queue<int> new_queue = std::queue<int>();
			
			while (_playerTurns.size() > 0)
			{
				int index = _playerTurns.front();
				_playerTurns.pop();

				if (index != player_index)
				{
					new_queue.push(index);
				}
			}

			_playerTurns = new_queue;
		}

		int get_next_player_index()
		{
			int index = _playerTurns.front();
			_playerTurns.pop();

			_playerTurns.push(index);

			return index;
		}
	};
}

#endif