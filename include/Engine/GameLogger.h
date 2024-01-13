// Author: Martina Naldoni

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