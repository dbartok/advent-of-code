#include "Day13-PointOfIncidence.h"

#include "MirrorFinder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day13
{

using MappingTextSection = std::vector<std::string>;

MirrorFinder parseMapTextSection(const MappingTextSection& mappingTextSection)
{
    Matrix matrix = Matrix::Zero(mappingTextSection.size(), mappingTextSection.front().size());

    for (int j = 0; j < mappingTextSection.size(); ++j)
    {
        for (int i = 0; i < mappingTextSection.front().size(); ++i)
        {
            if (mappingTextSection.at(j).at(i) == '#')
            {
                matrix(j, i) = 1;
            }
        }
    }

    return MirrorFinder{std::move(matrix)};
}

std::vector<MirrorFinder> parseMapLines(const std::vector<std::string>& mapLines)
{
    std::vector<MappingTextSection> mapTextSections;
    boost::split(mapTextSections, mapLines, [](const auto& elem) { return elem.empty(); });

    std::vector<MirrorFinder> mirrorFinders;
    for (const auto& mapTextSection : mapTextSections)
    {
        MirrorFinder mirrorFinder = parseMapTextSection(mapTextSection);
        mirrorFinders.push_back(std::move(mirrorFinder));
    }
    return mirrorFinders;
}

int numberAfterSummarizingAllNotes(const std::vector<std::string>& mapLines)
{
    std::vector<MirrorFinder> mirrorFinders = parseMapLines(mapLines);

    return std::accumulate(mirrorFinders.begin(), mirrorFinders.end(), 0, [](int acc, auto& mirrorFinder)
                           {
                               mirrorFinder.find();
                               return acc + mirrorFinder.getNoteNumber();
                           });
}

int numberAfterSummarizingAllNotesWithSmudge(const std::vector<std::string>& mapLines)
{
    std::vector<MirrorFinder> mirrorFinders = parseMapLines(mapLines);

    return std::accumulate(mirrorFinders.begin(), mirrorFinders.end(), 0, [](int acc, auto& mirrorFinder)
                           {
                               mirrorFinder.findSmudged();
                               return acc + mirrorFinder.getNoteNumber();
                           });
}

}
}
}