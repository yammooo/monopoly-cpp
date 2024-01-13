// Author: Luca Bonaldo

#ifndef SERVICE_PROVIDER_HPP
#define SERVICE_PROVIDER_HPP

namespace dependency_injection
{
    template <class T, class... Args>
    void ServiceProvider::register_service(Args&&... args)
    {
        auto name = typeid(T).name();
        
        // if services with given name are found, throw
        if (_services.count(name) > 0)
        {
            throw dependency_injection::ServiceAlreadyRegisteredException();
        }

        // insert the configured service into the pool
        _services.insert({name, std::make_shared<T>(args...)});
    }

    template <class T>
    T* ServiceProvider::get_service()
    {   
        auto name = typeid(T).name();

        // if the service is not found, throw
        if (_services.count(name) != 1)
        {
            throw dependency_injection::ServiceNotRegisteredException();
        }

        // pointer to the registered service
        return (std::static_pointer_cast<T>(_services[name])).get();
    }
}

#endif // SERVICE_PROVIDER_HPP