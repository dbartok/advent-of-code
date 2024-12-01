#include "Day08-MemoryManeuver.h"

#include "LicenseTree.h"
#include "LicenseNode.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stack>
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day08
{

LicenseNodeSharedPtr parseChild(std::vector<unsigned>::const_iterator& nodeNumbersIter)
{
    LicenseNodeSharedPtr child = std::make_shared<LicenseNode>(*nodeNumbersIter, *(nodeNumbersIter + 1));
    nodeNumbersIter += 2;

    return child;
}

Metadatum parseMetadatum(std::vector<unsigned>::const_iterator& nodeNumbersIter)
{
    return *(nodeNumbersIter++);
}

LicenseNodeSharedPtr parseLicenseTreeRoot(const std::vector<unsigned>& nodeNumbers)
{
    auto nodeNumbersIter = nodeNumbers.cbegin();
    LicenseNodeSharedPtr rootNode = std::make_shared<LicenseNode>(*nodeNumbersIter, *(nodeNumbersIter + 1));
    nodeNumbersIter += 2;

    std::stack<LicenseNodeSharedPtr> parseStack;
    parseStack.push(rootNode);

    while (!parseStack.empty())
    {
        auto currentNodeParsed = parseStack.top();

        if (!currentNodeParsed->areChildrenFull())
        {
            LicenseNodeSharedPtr childSharedPtr = parseChild(nodeNumbersIter);

            currentNodeParsed->addChild(childSharedPtr);
            parseStack.push(std::move(childSharedPtr));
        }
        else if (!currentNodeParsed->isMetadataFull())
        {
            currentNodeParsed->addMetadatum(parseMetadatum(nodeNumbersIter));
        }
        else
        {
            parseStack.pop();
        }
    }

    return rootNode;
}

unsigned sumOfAllMetadataEntries(const std::vector<unsigned>& nodeNumbers)
{
    LicenseNodeSharedPtr rootSharedPtr = parseLicenseTreeRoot(nodeNumbers);
    LicenseTree licenseTree{std::move(rootSharedPtr)};

    return licenseTree.getSumOfAllMetadata();
}

unsigned valueOfRootNode(const std::vector<unsigned>& nodeNumbers)
{
    LicenseNodeSharedPtr rootSharedPtr = parseLicenseTreeRoot(nodeNumbers);
    LicenseTree licenseTree{std::move(rootSharedPtr)};

    return licenseTree.getValueOfRootNode();
}

}
}
}
