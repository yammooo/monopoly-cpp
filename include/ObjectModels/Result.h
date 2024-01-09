// Author: Luca Bonaldo

#ifndef RESULT_H
#define RESULT_H

#include <string>

namespace object_models
{
    template <typename T>
    class Result
    {
        private:

        bool _isError;

        T _value;
        std::string _error;

        Result() {}
        
        Result(std::string error) { _error = error; _isError = true; }
        Result(T value) { _value = value; _isError = false; }

        public:

        static Result<T> Error(std::string message);
        static Result<T> Ok(T value);

        T value();
        std::string error();

        bool isError();

    };
    
    template <typename T>
    inline Result<T> Result<T>::Error(std::string message)
    {
        return Result<T>(message);
    }
    
    template <typename T>
    inline Result<T> Result<T>::Ok(T value)
    {
        return Result<T>(value);
    }
    
    template <typename T>
    inline T Result<T>::value()
    {
        return _value;
    }
    
    template <typename T>
    inline std::string Result<T>::error()
    {
        return _error;
    }

    template <typename T>
    inline bool Result<T>::isError()
    {
        return _isError;
    }
}

#endif // RESULT