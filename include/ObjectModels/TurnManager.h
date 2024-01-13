// Author: Gianmaria Frigo

#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include <queue>
#include <vector>

namespace object_models
{
	// The TurnManager class is responsible for managing the order of turns in the game.
	class TurnManager
	{
		private:

			// Queue of player turns. Each entry is the index of a player.
			std::queue<int> _playerTurns;

		public:

			TurnManager() {};

			// Constructor that initializes the TurnManager with a vector representing the order player turns.
			explicit TurnManager(std::vector<int> turns);

			// Removes the player at the given index from the queue.
			void remove_player(int player_index);

			// Used to advance the turn to the next player.
			void next_turn();

			int get_current_player_index();
	};
}

#endif