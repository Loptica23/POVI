#pragma once
#include <memory>
#include <vector>

namespace Utils
{

template<typename T, typename FT>
std::shared_ptr<T> findElementInVectorPtr(std::shared_ptr<std::vector<std::shared_ptr<T>>> vector, const FT & findValue, FT (T::*function)() const)
{
    std::shared_ptr<T> result = nullptr;

    auto it = std::find_if(vector->begin(), vector->end(), [&](std::shared_ptr<T> const & elementPtr)
            {
                return ((*elementPtr).*(function))() == findValue;
            });

    if (it != vector->end())
    {
        result = *it;
    }
    return result;
}

template<typename T, typename FT>
std::shared_ptr<T> findElementInVectorPtr(std::shared_ptr<std::vector<std::shared_ptr<T>>> vector, const FT & findValue, const FT & (T::*function)() const)
{
    std::shared_ptr<T> result = nullptr;

    auto it = std::find_if(vector->begin(), vector->end(), [&](std::shared_ptr<T> const & elementPtr)
            {
                return ((*elementPtr).*(function))() == findValue;
            });

    if (it != vector->end())
    {
        result = *it;
    }
    return result;
}


}
