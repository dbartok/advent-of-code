#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <memory>
#include <functional>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day08
{

class LicenseNode;
using LicenseNodeSharedPtr = std::shared_ptr<LicenseNode>;

using Metadatum = unsigned;

class LicenseNode
{
public:
    LicenseNode(unsigned expectedChildCount, unsigned expectedMetadataCount) noexcept;

    bool areChildrenFull() const noexcept;
    bool isMetadataFull() const noexcept;

    Metadatum getSumOfMetadata() const;
    const std::vector<LicenseNodeSharedPtr>& getChildren() const noexcept;
    std::vector<LicenseNodeSharedPtr> getChildrenIdentifiedByMetadata() const;

    void addChild(LicenseNodeSharedPtr childSharedPtr);
    void addMetadatum(Metadatum metadatum);

private:
    unsigned m_expectedChildCount;
    unsigned m_expectedMetadataCount;

    std::vector<LicenseNodeSharedPtr> m_childrenSharedPtrs;
    std::vector<Metadatum> m_metadata;
};

}
}
}
