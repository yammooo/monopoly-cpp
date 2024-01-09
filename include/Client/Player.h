// Author: Martina Naldoni

#ifndef PLAYER_H
#define PLAYER_H

#include "../Interfaces/IPlayer.h"

namespace client
{
	class Player : public interfaces::IPlayer
	{
		private:

		public:

		object_models::ActionInfo get_action(object_models::GameInfo info);

	};
}

#endif // PLAYER_H
