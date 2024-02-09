#pragma once
#include <vector>
#include <memory>
#include <span>

class PointerHelper
{
public:

    template<typename T>
    static std::span<T*> GetPointersSpan(std::vector<std::unique_ptr<T>> vector);  
};

template<typename T>
static std::span<T*> PointerHelper::GetPointersSpan(std::vector<std::unique_ptr<T>> vector)
{
    std::vector<T*> rawPointers;
    rawPointers.reserve(vector.size());

    std::transform(vector.begin(), vector.end(), std::back_inserter(rawPointers),
        [](const UniquePtrType& ptr) { return ptr.get(); });

    return std::span<T*>(rawPointers.data(), rawPointers.size());
}