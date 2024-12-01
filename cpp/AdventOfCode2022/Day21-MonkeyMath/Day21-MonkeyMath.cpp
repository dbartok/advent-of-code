#include "Day21-MonkeyMath.h"

#include "MonkeyParser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day21
{

int64_t numberYelledByRootMonkey(const std::vector<std::string>& monkeyLines)
{
    MonkeyParser monkeyParser{monkeyLines};

    monkeyParser.parse();

    auto rootNode = monkeyParser.getRootNode();

    return rootNode->evaluate();
}

int64_t numberYelledByHumanToPassEqualityTest(const std::vector<std::string>& monkeyLines)
{
    MonkeyParser monkeyParser{monkeyLines};

    monkeyParser.parse();

    auto rootNode = monkeyParser.getRootNode();
    auto humanNode = monkeyParser.getHumanNode();

    auto fixedValueSubtree = rootNode->getLeftOperandNode();
    auto variableValueSubtree = rootNode->getRightOperandNode();

    if (fixedValueSubtree->getIsAncestorOfHumanNode())
    {
        std::swap(fixedValueSubtree, variableValueSubtree);
    }

    const int64_t equationFixedSideValue = fixedValueSubtree->evaluate();

    variableValueSubtree->forceEvaluateTo(equationFixedSideValue);

    return humanNode->evaluate();
}

}
}
}