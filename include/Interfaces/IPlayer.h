// Author: Luca Bonaldo

#ifndef I_PLAYER_H
#define I_PLAYER_H

#include "../ObjectModels/GameInfo.h"
#include "../ObjectModels/ActionInfo.h"

namespace interfaces
{
	/// <summary>
	/// Interfaces that specifies the signature of a player
	/// </summary>
	class IPlayer
	{
	private:
	public:

		/// <summary>
		/// Get the action to perform from the player
		/// </summary>
		/// <param name="info">The game info</param>
		/// <returns>The action chosen</returns>
		virtual object_models::ActionInfo get_action(object_models::GameInfo info) = 0;
	};
}

#endif // I_PLAYER_H