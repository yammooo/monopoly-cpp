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
        
        template <class T, class... Args>
        static void register_service(Args&&... args);

        template <class T>
        static T* get_service();
    };
}

#include "ServiceProvider.hpp"

#endif // SERVICE_PROVIDER_H