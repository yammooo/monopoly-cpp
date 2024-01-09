// Author: Luca Bonaldo

#ifndef I_PLAYER_H
#define I_PLAYER_H

#include "../ObjectModels/GameInfo.h"
#include "../ObjectModels/ActionInfo.h"

namespace interfaces
{
	class IPlayer
	{
	private:
	public:

		virtual object_models::ActionInfo get_action(object_models::GameInfo info) = 0;
	};
}

#endif // I_PLAYER_H