#include "Day13-TransparentOrigami.h"

#include "TransparentPaperFolder.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day13
{

using TextSection = std::vector<std::string>;

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

std::string thermalCameraActivationCode(const std::vector<std::string>& instructionManualLines)
{
    TransparentPaperFolder transparentPaperFolder = parseInstructionManualLines(instructionManualLines);
    transparentPaperFolder.foldCompletely();
    return transparentPaperFolder.getSerializedMessage();
}

}
}
}