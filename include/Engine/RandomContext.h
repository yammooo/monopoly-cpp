// Author: Luca Bonaldo

#ifndef RANDOM_CONTEXT_H
#define RANDOM_CONTEXT_H

#include <random>

namespace engine
{
    class RandomContext
    {
        private:

        std::random_device _device;
        std::mt19937 _rng;

        public:

        RandomContext();
        RandomContext(int seed);

        double get_next();
        int get_next(int upperBound);
        int get_next(int lowerBound, int upperBound);
    };
}

#endif // RANDOM_CONTEXT_H