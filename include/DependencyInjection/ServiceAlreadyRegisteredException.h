// Author: Luca Bonaldo

#ifndef SERVICE_ALREADY_REGISTERED_EXCEPTION_H
#define SERVICE_ALREADY_REGISTERED_EXCEPTION_H

#include <exception>

namespace dependency_injection
{
    /// <summary>
    /// Exception thrown when a service is already registered
    /// </summary>
    class ServiceAlreadyRegisteredException : public std::exception
    {
        public:

        ServiceAlreadyRegisteredException() : std::exception() {}

        const char * what() const noexcept override
        {
            return "Service with specified name already registered.";
        }
    };
}

#endif // SERVICE_ALREADY_REGISTERED_EXCEPTION_H