// Author: Martina Naldoni

// we use std methods to generate random numbers 

#include "../../include/Engine/RandomContext.h"

engine::RandomContext::RandomContext()
{
    _rng = std::mt19937(_device());
}

engine::RandomContext::RandomContext(int seed)
{
}

double engine::RandomContext::get_next()
{
    std::uniform_real_distribution<>dist(0, 1.0);

    return dist(_rng);
}

int engine::RandomContext::get_next(int upperBound)
{
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, upperBound);

    return dist(_rng);
}
int engine::RandomContext::get_next(int lowerBound, int upperBound)
{
    std::uniform_int_distribution<std::mt19937::result_type> dist(lowerBound, upperBound);

    return dist(_rng);
}