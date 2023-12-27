#ifndef GAME_LOGGER_H
#define GAME_LOGGER_H

#include <ostream>
#include <vector>

namespace engine
{
	class GameLogger
	{
		private:

		std::vector<std::ostream*> _streams;

		public:
		
		GameLogger(std::vector<std::ostream*> streams) { _streams = streams; }

		void print(const std::string& str) const
		{
			for (auto stream : _streams)
			{
				(*stream) << str << std::endl;
			}
		}
	};
}

#endif // !GAME_LOGGER_H