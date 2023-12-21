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
        static void register_service(Args&&... args)
        {
            auto name = typeid(T).name();

            if (_services.count(name) > 0)
            {
                throw dependency_injection::ServiceAlreadyRegisteredException();
            }

            _services.insert({name, std::make_shared<T>(args...)});
        }

        template <class T>
        static T get_service()
        {   
            auto name = typeid(T).name();

            if (_services.count(name) != 1)
            {
                throw dependency_injection::ServiceNotRegisteredException();
            }

            return *(std::static_pointer_cast<T>(_services[name]));
        }
    };
}

#endif // SERVICE_PROVIDER_H