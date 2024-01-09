// Author: Gianmaria Frigo

#ifndef PLAYER_NUMBER_MISMATCH_EXCEPTION_H
#define PLAYER_NUMBER_MISMATCH_EXCEPTION_H

#include <exception>

namespace client
{
    class PlayerNumberMismatchException : public std::exception
    {
        public:
            const char* what() const throw()
            {
                return "The number of players from the configuration does not match the number of players in the GameInfo.";
            }
    };
}

#endif // PLAYER_NUMBER_MISMATCH_EXCEPTION_H