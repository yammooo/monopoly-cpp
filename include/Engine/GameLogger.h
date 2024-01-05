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

		std::vector<std::ostream*> _streams;
		std::vector<std::string> _strings;

		public:
		
		GameLogger(std::vector<std::ostream*> streams) { _streams = streams; }
		GameLogger() { }

		void print(const std::string& str) const
		{
			for (auto stream : _streams)
			{
				(*stream) << str << std::endl;
			}
		}


		void log_action (const std::string& str){

			_strings.push_back(str);
			std::cout<<str<<std::endl;

		}



	};
}

#endif // !GAME_LOGGER_H