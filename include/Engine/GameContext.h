#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

namespace engine
{
    class GameContext
    {
        private:

        int _a;

        public:

        GameContext(int a)
        {
            _a = a;
        }

        int getA()
        {
            return _a;
        }

    };
}

#endif // GAME_CONTEXT_H