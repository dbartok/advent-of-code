#include "Day07-RecursiveCircus.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day07;

    std::fstream fileIn("input.txt");
    std::vector<CurrentDay::NodeDescriptor> nodeDescriptors;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        CurrentDay::NodeDescriptor nodeDescriptor = CurrentDay::NodeDescriptor::fromString(lineBuffer);
        nodeDescriptors.push_back(std::move(nodeDescriptor));
    }

    std::cout << "First part: " << CurrentDay::nameOfBottomProgram(nodeDescriptors) << std::endl;
    std::cout << "Second part: " << CurrentDay::correctWeightOfWrongWeight(nodeDescriptors) << std::endl;
}
