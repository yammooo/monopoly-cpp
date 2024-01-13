// Author: Luca Bonaldo

#ifndef SERVICE_NOT_REGISTERED_EXCEPTION_H
#define SERVICE_NOT_REGISTERED_EXCEPTION_H

#include <exception>

namespace dependency_injection
{
    /// <summary>
    /// Exception thrown when a service is not registered
    /// </summary>
    class ServiceNotRegisteredException : public std::exception
    {
        public:

        ServiceNotRegisteredException() : std::exception() {}

        const char * what() const noexcept override
        {
            return "No service with specified name registered.";
        }
    };
}

#endif // SERVICE_NOT_REGISTERED_EXCEPTION_H