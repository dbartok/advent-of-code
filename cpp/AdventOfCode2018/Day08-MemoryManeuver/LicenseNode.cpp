#include "LicenseNode.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day08
{

LicenseNode::LicenseNode(unsigned expectedChildCount, unsigned expectedMetadataCount) noexcept
    : m_expectedChildCount{expectedChildCount}
    , m_expectedMetadataCount{expectedMetadataCount}
{

}

bool LicenseNode::areChildrenFull() const noexcept
{
    return m_childrenSharedPtrs.size() == m_expectedChildCount;
}

bool LicenseNode::isMetadataFull() const noexcept
{
    return m_metadata.size() == m_expectedMetadataCount;
}

Metadatum LicenseNode::getSumOfMetadata() const
{
    const Metadatum sum = std::accumulate(m_metadata.cbegin(), m_metadata.cend(), Metadatum{},
                                    [](Metadatum acc, const Metadatum& metadatum) noexcept
                                    {
                                        return acc + metadatum;
                                    });
    return sum;
}

const std::vector<LicenseNodeSharedPtr>& LicenseNode::getChildren() const noexcept
{
    return m_childrenSharedPtrs;
}

std::vector<LicenseNodeSharedPtr> LicenseNode::getChildrenIdentifiedByMetadata() const
{
    std::vector<LicenseNodeSharedPtr> childrenIdentifiedByMetadata;

    for (const auto& metadatum : m_metadata)
    {
        if (metadatum != 0 && metadatum <= m_childrenSharedPtrs.size())
        {
            childrenIdentifiedByMetadata.push_back(m_childrenSharedPtrs[metadatum - 1]);
        }
    }

    return childrenIdentifiedByMetadata;
}

void LicenseNode::addChild(LicenseNodeSharedPtr childSharedPtr)
{
    m_childrenSharedPtrs.push_back(std::move(childSharedPtr));
}

void LicenseNode::addMetadatum(Metadatum metadatum)
{
    m_metadata.push_back(std::move(metadatum));
}

}
}
}
