#include "../../include/Engine/GameLogger.h"

using namespace engine;

std::string GameLogger::log_to_string() const
{
    std::string result = "";

    for (auto str : _strings)
    {
        result += str + "\n";
    }

    return result;
}