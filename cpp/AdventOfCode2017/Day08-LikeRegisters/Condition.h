#pragma once

#include "State.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day08
{

class Condition
{
public:
    Condition(std::string registerName, std::string symbol, int argument) noexcept;
    bool isTrue(const State& state) const;

private:
    std::string m_registerName;
    std::string m_symbol;
    int m_argument;
};

}
}
}
