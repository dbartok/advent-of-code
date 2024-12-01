#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>
#include <boost/optional.hpp>
#include <Eigen/dense>

#include <unordered_map>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day10
{

using Vector2D = Eigen::Vector2i;

struct Vector2DHash
{
    size_t operator()(const Vector2D& vec) const
    {
        std::size_t seed = 0;

        boost::hash_combine(seed, vec.x());
        boost::hash_combine(seed, vec.y());

        return seed;
    }
};

using Flow = std::pair<Vector2D, Vector2D>;

class PipeNetworkTraverser
{
public:
    PipeNetworkTraverser(std::vector<std::string> pipeNetwork);

    void traverseMainLoop();

    int getMainLoopLength() const;
    int getNumTilesEnclosedByMainLoop() const;

private:
    std::vector<std::string> m_pipeNetwork;
    size_t m_height;
    size_t m_width;
    std::unordered_map<char, Flow> m_pipeTypeToInwardsFlow;
    Vector2D m_start;

    std::unordered_set<Vector2D, Vector2DHash> m_mainLoopTiles;

    void initializePipeTypeToInwardsFlowMapping();
    void findStartPosition();

    std::vector<Vector2D> getValidDirectionsFrom(const Vector2D& origin) const;
    boost::optional<Vector2D> getStepResultIncludingOneFlow(const Vector2D& originTileCoordinates, const Vector2D& direction) const;
    bool isInbounds(const Vector2D& coordinates) const;

    bool isTileEnclosedByMainLoop(const Vector2D& coordinates) const;

    char tileAt(const Vector2D& coordinates) const;
    char& tileAt(const Vector2D& coordinates);
};

}
}
}
