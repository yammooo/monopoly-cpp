// Author: Luca Bonaldo

#ifndef RESULT_H
#define RESULT_H

#include <string>

namespace object_models
{
    /// <summary>
    /// Class that can hold a valid value or an error
    /// </summary>
    /// <typeparam name="T"></typeparam>
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

        /// <summary>
        /// Returns a Result<T> that is a error with given message
        /// </summary>
        /// <param name="message">The message of the error</param>
        /// <returns>The result containing the error</returns>
        static Result<T> Error(std::string message);

        /// <summary>
        /// Returns a Result<T> that is ok with given value
        /// </summary>
        /// <param name="value">The value containeds</param>
        /// <returns>The result</returns>
        static Result<T> Ok(T value);

        /// <summary>
        /// Gets the value contained if the object is not an error
        /// </summary>
        T value();

        /// <summary>
        /// Returns the error if the object is error
        /// </summary>
        std::string error();

        /// <summary>
        /// True if error; false otherwise
        /// </summary>
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