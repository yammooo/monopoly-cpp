// Author: Luca Bonaldo

#ifndef SERVICE_PROVIDER_H
#define SERVICE_PROVIDER_H

#include <map>
#include <memory>
#include <string>
#include <typeinfo>

#include "ServiceAlreadyRegisteredException.h"
#include "ServiceNotRegisteredException.h"

typedef std::map<std::string, std::shared_ptr<void>> __services_map;

namespace dependency_injection
{
    class ServiceProvider
    {
        private:

        static __services_map _services;

        public:
        
        /// <summary>
        /// Register a service to the dependency injection pool
        /// </summary>
        /// <typeparam name="T">The type of the service to register</typeparam>
        /// <typeparam name="...Args">The argument types needed to be passed to the service constructor</typeparam>
        /// <param name="...args">The arguments needed to be passed to the service constructor</param>
        template <class T, class... Args>
        static void register_service(Args&&... args);

        /// <summary>
        /// Return a registered and configured service from the pool
        /// </summary>
        /// <typeparam name="T">The type of the service to return</typeparam>
        /// <returns>The configured service</returns>
        template <class T>
        static T* get_service();
    };
}

#include "ServiceProvider.hpp"

#endif // SERVICE_PROVIDER_H