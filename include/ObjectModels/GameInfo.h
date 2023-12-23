#ifndef GAME_RESULT_H
#define GAME_RESULT_H

#include "GameData.h"

namespace object_models
{
    class GameInfo
    {
        private:

        int _id;

        public:

        int id() { return _id; }

        GameInfo() {}
        GameInfo(int id);
        GameInfo(object_models::GameData game);
    };
}

#endif // GAME_RESULT_H