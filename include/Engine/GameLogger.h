// Author: Martina Naldoni

/*
Game logger is a class that instantiates the object gamelogger,
that is a vector of strings that contains every action taken in the game.

It is mainly used in gameprocessor: after the game is updated with the latest move,
log_action is called, to insert the string version of the move in the game's logger

it only contains the actions required to be printed in the output.
*/

#ifndef GAME_LOGGER_H
#define GAME_LOGGER_H

#include <iostream>
#include <vector>
#include <string>

namespace engine
{
	class GameLogger
	{
		private:

		std::vector<std::string> _strings;

		public:

		GameLogger() {}

		void log_action (const std::string& str) { _strings.push_back(str); }

		std::string log_to_string() const;

	};
}

#endif // GAME_LOGGER_H