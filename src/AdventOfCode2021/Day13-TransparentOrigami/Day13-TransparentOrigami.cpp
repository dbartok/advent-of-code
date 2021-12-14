#include "Day13-TransparentOrigami.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>
#include <boost/algorithm/string.hpp>

#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day13
{

enum class Axis
{
    X,
    Y,
};

struct FoldInstruction
{
    Axis axis;
    int position;
};

using FoldInstructions = std::vector<FoldInstruction>;

using Coordinates = std::pair<int, int>;
using CoordinatesSet = std::unordered_set<Coordinates, boost::hash<Coordinates>>;

using TextSection = std::vector<std::string>;

class TransparentPaperFolder
{
public:
    TransparentPaperFolder(CoordinatesSet dotCoordinatesSet, FoldInstructions foldInstructions)
        : m_dotCoordinatesSet{std::move(dotCoordinatesSet)}
        , m_foldInstructions{std::move(foldInstructions)}
    {

    }

    void foldOnce()
    {
        const auto& currentInstruction = m_foldInstructions.at(m_instructionIndex++);
        if (currentInstruction.axis == Axis::Y)
        {
            foldBottomHalfUp(currentInstruction.position);
        }
        else
        {
            foldRightHalfLeft(currentInstruction.position);
        }
    }

    unsigned getNumVisibleDots() const
    {
        return m_dotCoordinatesSet.size();
    }

private:
    CoordinatesSet m_dotCoordinatesSet;
    FoldInstructions m_foldInstructions;

    size_t m_instructionIndex = 0;

    void foldBottomHalfUp(int yThreshold)
    {
        std::vector<Coordinates> dotCoordatinesVector{m_dotCoordinatesSet.cbegin(), m_dotCoordinatesSet.cend()};
        for (auto dotCoordinates : dotCoordatinesVector)
        {
            if (dotCoordinates.second > yThreshold)
            {
                m_dotCoordinatesSet.erase(dotCoordinates);
                dotCoordinates.second = yThreshold - (dotCoordinates.second - yThreshold);
                m_dotCoordinatesSet.insert(dotCoordinates);
            }
        }
    }

    void foldRightHalfLeft(int xThreshold)
    {
        std::vector<Coordinates> dotCoordatinesVector{m_dotCoordinatesSet.cbegin(), m_dotCoordinatesSet.cend()};
        for (auto dotCoordinates : dotCoordatinesVector)
        {
            if (dotCoordinates.first > xThreshold)
            {
                m_dotCoordinatesSet.erase(dotCoordinates);
                dotCoordinates.first = xThreshold - (dotCoordinates.first - xThreshold);
                m_dotCoordinatesSet.insert(dotCoordinates);
            }
        }
    }
};

Coordinates parseCoordinatesLine(const std::string& coordinatesLine)
{
    std::vector<int> coordinates;
    Utils::splitStringIntoTypedVector(coordinatesLine, coordinates, ',');
    return Coordinates{coordinates.at(0), coordinates.at(1)};
}

Axis parseAxisString(const std::string& axisString)
{
    if (!(axisString == "x" || axisString == "y"))
    {
        throw std::runtime_error("Cannot parse axis: " + axisString);
    }
    return axisString == "x" ? Axis::X : Axis::Y;
}

FoldInstruction parseFoldInstructionLine(const std::string& foldInstructionLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, foldInstructionLine, boost::is_any_of(" ="));

    if (tokens.size() != 4)
    {
        throw std::runtime_error("Invalid number of tokens in line: " + foldInstructionLine);
    }

    const Axis axis = parseAxisString(tokens.at(2));
    const int position = std::stoi(tokens.at(3));

    return FoldInstruction{axis, position};
}

CoordinatesSet parseCoordinatesTextSection(const TextSection& coordinatesTextSection)
{
    CoordinatesSet coordinatesSet;

    for (const auto& line : coordinatesTextSection)
    {
        Coordinates coordinates = parseCoordinatesLine(line);
        coordinatesSet.insert(std::move(coordinates));
    }

    return coordinatesSet;
}

FoldInstructions parseFoldInstructionTextSection(const std::vector<std::string>& foldInstructionTextSection)
{
    FoldInstructions foldInstructions;

    for (const auto& line : foldInstructionTextSection)
    {
        FoldInstruction foldInstruction = parseFoldInstructionLine(line);
        foldInstructions.push_back(std::move(foldInstruction));
    }

    return foldInstructions;
}

TransparentPaperFolder parseInstructionManualLines(const std::vector<std::string>& instructionManualLines)
{
    std::vector<TextSection> textSections;
    boost::split(textSections, instructionManualLines, [](const auto& elem) { return elem.empty(); });

    CoordinatesSet dotCoordinatesSet = parseCoordinatesTextSection(textSections.at(0));
    FoldInstructions foldInstructions = parseFoldInstructionTextSection(textSections.at(1));

    return TransparentPaperFolder{std::move(dotCoordinatesSet), std::move(foldInstructions)};
}

unsigned numVisibleDotsAfterFirstFold(const std::vector<std::string>& instructionManualLines)
{
    TransparentPaperFolder transparentPaperFolder = parseInstructionManualLines(instructionManualLines);
    transparentPaperFolder.foldOnce();
    return transparentPaperFolder.getNumVisibleDots();
}

}
}
}