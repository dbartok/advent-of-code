#include "LicenseTree.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day08
{

LicenseTree::LicenseTree(LicenseNodeSharedPtr rootSharedPtr) noexcept
    : m_rootSharedPtr{std::move(rootSharedPtr)}
{

}

Metadatum LicenseTree::getSumOfAllMetadata() const
{
    return getSumOfAllMetadataRecursive(*m_rootSharedPtr);
}

Metadatum LicenseTree::getValueOfRootNode() const
{
    return getValueOfRootNodeRecursive(*m_rootSharedPtr);
}

Metadatum LicenseTree::getSumOfAllMetadataRecursive(const LicenseNode& root)
{
    const std::vector<LicenseNodeSharedPtr>& childrenSharedPtrs = root.getChildren();
    const Metadatum sumForChildren = accumulateNodes<Metadatum>(childrenSharedPtrs, getSumOfAllMetadataRecursive);

    return root.getSumOfMetadata() + sumForChildren;
}

Metadatum LicenseTree::getValueOfRootNodeRecursive(const LicenseNode& root)
{
    if (root.getChildren().empty())
    {
        return root.getSumOfMetadata();
    }

    std::vector<LicenseNodeSharedPtr> childrenIdentifiedByMetadata = root.getChildrenIdentifiedByMetadata();
    const Metadatum sumForChildren = accumulateNodes<Metadatum>(childrenIdentifiedByMetadata, getValueOfRootNodeRecursive);

    return sumForChildren;
}

}
}
}
