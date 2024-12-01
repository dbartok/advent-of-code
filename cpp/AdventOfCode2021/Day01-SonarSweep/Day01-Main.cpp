#include "Day01-SonarSweep.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/lexical_cast.hpp>

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2021::Day01;

    std::fstream fileIn("input.txt");
    std::vector<unsigned> depthMeasurements;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        const unsigned depthMeasurement = boost::lexical_cast<unsigned>(lineBuffer);
        depthMeasurements.push_back(depthMeasurement);
    }

    std::cout << "First part: " << CurrentDay::numDepthMeasurementIncreases(depthMeasurements) << std::endl;
    std::cout << "Second part: " << CurrentDay::numDepthMeasurementIncreasesWithRollingWindow(depthMeasurements) << std::endl;
}
