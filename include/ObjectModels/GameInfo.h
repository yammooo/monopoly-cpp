#ifndef GAME_RESULT_H
#define GAME_RESULT_H

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
    };
}

#endif // GAME_RESULT_H