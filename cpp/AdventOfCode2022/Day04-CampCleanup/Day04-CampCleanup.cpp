#include "Day04-CampCleanup.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day04
{

using Assignment = std::pair<int, int>;
using AssignmentPair = std::pair<Assignment, Assignment>;
using AssignmentPairs = std::vector<AssignmentPair>;

AssignmentPair parseAssignmentPairLine(const std::string& assignmentPairLine)
{
    std::vector<std::string> chunks;
    boost::split(chunks, assignmentPairLine, boost::is_any_of(",-"));

    Assignment firstAssigment{std::stoi(chunks.at(0)), std::stoi(chunks.at(1))};
    Assignment secondAssigment{std::stoi(chunks.at(2)), std::stoi(chunks.at(3))};

    return AssignmentPair{std::move(firstAssigment), std::move(secondAssigment)};
}

AssignmentPairs parseAssignmentPairLines(const std::vector<std::string>& assignmentPairLines)
{
    AssignmentPairs assignmentPairs;

    for (const auto& assignmentPairLine : assignmentPairLines)
    {
        AssignmentPair assignmentPair = parseAssignmentPairLine(assignmentPairLine);
        assignmentPairs.push_back(std::move(assignmentPair));
    }

    return assignmentPairs;
}

bool areAssignmentsContainedWithinEachOther(const AssignmentPair& assignmentPair)
{
    const Assignment& firstAssignment = assignmentPair.first;
    const Assignment& secondAssignment = assignmentPair.second;

    const Assignment extendedAssignment{std::min(firstAssignment.first, secondAssignment.first), std::max(firstAssignment.second, secondAssignment.second)};

    return (extendedAssignment == firstAssignment || extendedAssignment == secondAssignment);
}

bool areAssignmentsOverlapping(const AssignmentPair& assignmentPair)
{
    const Assignment& firstAssignment = assignmentPair.first;
    const Assignment& secondAssignment = assignmentPair.second;

    return !(firstAssignment.first > secondAssignment.second || secondAssignment.first > firstAssignment.second);
}

int numAssignmentPairsFullyContainingEachOther(const std::vector<std::string>& assignmentPairLines)
{
    AssignmentPairs assignmentPairs = parseAssignmentPairLines(assignmentPairLines);

    return std::count_if(assignmentPairs.cbegin(), assignmentPairs.cend(), areAssignmentsContainedWithinEachOther);
}

int numAssignmentPairsOverlapping(const std::vector<std::string>& assignmentPairLines)
{
    AssignmentPairs assignmentPairs = parseAssignmentPairLines(assignmentPairLines);

    return std::count_if(assignmentPairs.cbegin(), assignmentPairs.cend(), areAssignmentsOverlapping);
}

}
}
}