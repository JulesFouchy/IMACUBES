#pragma once

#include "Debugging/Log.hpp"
#include "UniformDescriptionConcrete.hpp"

namespace UniformDescriptionFactory {
// public :
UniformDescription* FromShaderLine(const std::string& line, HistoryType historyType);

// private :
namespace { // anonymous namespace to make functions private
template<typename T>
T ReadValue(const std::string& str, size_t* currentPosPtr);

template<typename T>
UniformDescription* ReadNameAndValuesAndCreateUniformDescriptionOfType(const std::string& line, size_t posEndType, HistoryType historyType)
{
    // Get name
    size_t      posBeginName = MyString::BeginningOfNextWord(line, posEndType);
    size_t      posEndName   = MyString::EndOfNextWord(line, posBeginName);
    std::string s_name       = line.substr(posBeginName, posEndName - posBeginName);
    // Get options
    T      initialValue    = T(0);
    T      minValue        = T(0);
    T      maxValue        = T(1);
    size_t posBeginComment = line.find("//");
    if (posBeginComment != std::string::npos)
    {
        size_t currentPos = MyString::BeginningOfNextWord(line, MyString::EndOfNextWord(line, posBeginComment) + 1);
        while (currentPos < line.size())
        {
            std::string arg = MyString::GetNextWord(line, &currentPos);
            if (arg == "default")
            {
                initialValue = ReadValue<T>(line, &currentPos);
            }
            else if (arg == "min")
            {
                minValue = ReadValue<T>(line, &currentPos);
            }
            else if (arg == "max")
            {
                maxValue = ReadValue<T>(line, &currentPos);
            }
            else
            {
                if (!arg.empty())
                    spdlog::warn("[UniformDescriptionFactory::ReadNameAndValuesAndCreateUniformOfType] Unknown argument : '{}'", arg);
            }
        }
    }
    // Return uniform
    return new UniformDescriptionConcrete<T>(s_name, historyType, initialValue, minValue, maxValue);
}
} // namespace
} // namespace UniformDescriptionFactory