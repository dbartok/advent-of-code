#include "Scanner.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day19
{

Scanner::Scanner(int id, std::vector<Vector3D> beaconPositions)
    : m_id{id}
    , m_beaconPositions{std::move(beaconPositions)}
{

}

void Scanner::applyBaseTransform(const Matrix3D& baseTransformVector)
{
    for (auto& beaconPosition : m_beaconPositions)
    {
        beaconPosition = (beaconPosition * baseTransformVector).transpose();
    }
}

void Scanner::applyOffset(const Vector3D& offset)
{
    m_offset += offset;
    for (auto& beaconPosition : m_beaconPositions)
    {
        beaconPosition += offset;
    }
}

Vector3DSet Scanner::getPossibleOffsetsFrom(const Scanner& other) const
{
    Vector3DSet possibleOffsets;

    for (const auto& thisBeaconPosition : m_beaconPositions)
    {
        for (const auto& otherBeaconPosition : other.m_beaconPositions)
        {
            Vector3D possibleOffset = otherBeaconPosition - thisBeaconPosition;
            possibleOffsets.insert(possibleOffset);
        }
    }

    return possibleOffsets;
}

unsigned Scanner::getNumOverlappingBeacons(const Scanner& other) const
{
    Vector3DSet otherBeaconPositions{other.m_beaconPositions.cbegin(), other.m_beaconPositions.cend()};
    Vector3DSet beaconPositionsUnion = getBeaconPositionUnion(otherBeaconPositions);

    return m_beaconPositions.size() + other.m_beaconPositions.size() - beaconPositionsUnion.size();
}

Vector3DSet Scanner::getBeaconPositionUnion(Vector3DSet otherBeaconPositions) const
{
    Vector3DSet thisBeaconPositions{m_beaconPositions.cbegin(), m_beaconPositions.cend()};
    Vector3DSet beaconPositionsUnion;

    std::set_union(thisBeaconPositions.cbegin(), thisBeaconPositions.cend(),
                    otherBeaconPositions.cbegin(), otherBeaconPositions.cend(),
                    std::inserter(beaconPositionsUnion, beaconPositionsUnion.begin()),
                    Vector3DCmp{});

    return beaconPositionsUnion;
}

unsigned Scanner::getManhattanDistanceFrom(const Scanner& other) const
{
    return (other.m_offset - m_offset).cwiseAbs().sum();
}

int Scanner::getId()
{
    return m_id;
}

const Vector3D& Scanner::getOffset() const
{
    return m_offset;
}

bool Scanner::operator==(const Scanner& other) const
{
    return m_id == other.m_id;
}

}
}
}
