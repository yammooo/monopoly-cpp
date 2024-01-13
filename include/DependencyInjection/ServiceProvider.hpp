// Author: Luca Bonaldo

#ifndef SERVICE_PROVIDER_HPP
#define SERVICE_PROVIDER_HPP

namespace dependency_injection
{
    template <class T, class... Args>
    void ServiceProvider::register_service(Args&&... args)
    {
        auto name = typeid(T).name();

        if (_services.count(name) > 0)
        {
            throw dependency_injection::ServiceAlreadyRegisteredException();
        }

        _services.insert({name, std::make_shared<T>(args...)});
    }

    template <class T>
    T* ServiceProvider::get_service()
    {   
        auto name = typeid(T).name();

        if (_services.count(name) != 1)
        {
            throw dependency_injection::ServiceNotRegisteredException();
        }

        return (std::static_pointer_cast<T>(_services[name])).get();
    }
}

#endif // SERVICE_PROVIDER_HPP