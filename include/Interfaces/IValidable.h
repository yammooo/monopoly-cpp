// Author: Luca Bonaldo

#ifndef I_VALIDABLE_H
#define I_VALIDABLE_H

namespace interfaces
{
    /// <summary>
    /// Interfaces for objects that need to be validated
    /// </summary>
    class IValidable
    {
        public:
        
        /// <summary>
        /// Specifies if the object is valid
        /// </summary>
        /// <returns>True if the object is valid; false otherwise</returns>
        virtual bool is_valid() = 0;
    };
}


#endif