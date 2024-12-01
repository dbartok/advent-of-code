#include "NodeDescriptor.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day07
{

NodeDescriptor::NodeDescriptor(std::string name, int weight, std::vector<std::string> childrenNames) noexcept
    : name{std::move(name)}
    , weight{weight}
    , childrenNames{std::move(childrenNames)}
{

}

NodeDescriptor NodeDescriptor::fromString(const std::string& nodeDescriptorString)
{
    std::vector<std::string> tokens;
    boost::split(tokens, nodeDescriptorString, boost::is_any_of("\t, "), boost::token_compress_on);

    if (tokens.size() < 2)
    {
        throw(std::runtime_error("Input string has too few tokens."));
    }

    std::string name = tokens[0];

    std::string weightToken = tokens[1];
    if (weightToken.size() < 3 || weightToken.front() != '(' || weightToken.back() != ')')
    {
        throw(std::runtime_error("Weight token has incorrect format."));

    }

    std::string strippedWeightToken = weightToken.substr(1, weightToken.size() - 2);
    int weight = std::stoi(strippedWeightToken);

    std::vector<std::string> childrenNames;
    if (tokens.size() >= 3)
    {
        std::for_each(tokens.begin() + 3, tokens.end(), [&childrenNames](std::string str) { childrenNames.push_back(std::move(str)); });
    }

    return NodeDescriptor{name, weight, childrenNames};
}

}
}
}
