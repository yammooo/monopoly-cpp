// Luca Bonaldo

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

		Bot()
		{
			_random = dependency_injection::ServiceProvider::get_service<engine::RandomContext>();
		}

		object_models::ActionInfo get_action(object_models::GameInfo info);
	};
}

#endif // BOT_H
