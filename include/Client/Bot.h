// Author: Luca Bonaldo

#ifndef BOT_H
#define BOT_H

#include "../Interfaces/IPlayer.h"

#include "../Engine/RandomContext.h"
#include "../DependencyInjection/ServiceProvider.h"

namespace client
{
	class Bot : public interfaces::IPlayer
	{
		private:

		engine::RandomContext* _random;

		public:

		/// <summary>
		/// Default constructor
		/// </summary>
		Bot()
		{
			_random = dependency_injection::ServiceProvider::get_service<engine::RandomContext>();
		}

		/// <summary>
		/// Get the action from the bot
		/// </summary>
		/// <param name="info">The game info from which the action should be taken</param>
		/// <returns>The action decided</returns>
		object_models::ActionInfo get_action(object_models::GameInfo info);
	};
}

#endif // BOT_H
