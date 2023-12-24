#ifndef BOT_H
#define BOT_H

#include "../Interfaces/IPlayer.h"

namespace client
{
	class Bot : public interfaces::IPlayer
	{
	private:

	public:

		object_models::ActionInfo get_action(object_models::GameInfo info) { return object_models::ActionInfo(); }

	};
}

#endif // !BOT_H
