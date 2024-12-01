#pragma once

#include "LicenseNode.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day08
{

class LicenseTree
{
public:
    LicenseTree(LicenseNodeSharedPtr rootSharedPtr) noexcept;

    Metadatum getSumOfAllMetadata() const;
    Metadatum getValueOfRootNode() const;

private:
    LicenseNodeSharedPtr m_rootSharedPtr;

    static Metadatum getSumOfAllMetadataRecursive(const LicenseNode& root);
    static Metadatum getValueOfRootNodeRecursive(const LicenseNode& root);

    template <typename AccumulationResultType>
    static AccumulationResultType accumulateNodes(const std::vector<LicenseNodeSharedPtr>& nodeSharedPtrs, std::function<AccumulationResultType(const LicenseNode&)> accumulatorFunc);
};

template <typename AccumulationResultType>
static AccumulationResultType LicenseTree::accumulateNodes(const std::vector<LicenseNodeSharedPtr>& nodeSharedPtrs, std::function<AccumulationResultType(const LicenseNode&)> accumulatorFunc)
{
    AccumulationResultType accumulatedNodes = std::accumulate(nodeSharedPtrs.cbegin(), nodeSharedPtrs.cend(), AccumulationResultType{},
                                                              [accumulatorFunc](AccumulationResultType acc, const LicenseNodeSharedPtr& childSharedPtr)
                                                              {
                                                                  return acc + accumulatorFunc(*childSharedPtr);
                                                              });

    return accumulatedNodes;
}

}
}
}
