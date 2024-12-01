#include "Day15-LensLibrary.h"

#include "InitializationSequenceAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day15
{

std::vector<std::string> parseInitializationSequenceString(const std::string& initializationSequenceString)
{
    std::vector<std::string> initializationSequence;
    boost::split(initializationSequence, initializationSequenceString, boost::is_any_of(","));
    return initializationSequence;
}

int sumOfHashResults(const std::string& initializationSequenceString)
{
    std::vector<std::string> initializationSequence = parseInitializationSequenceString(initializationSequenceString);

    InitializationSequenceAnalyzer initializationSequenceAnalyzer{std::move(initializationSequence)};

    return initializationSequenceAnalyzer.getSumOfInitializationSequenceHashes();
}

int focusingPowerOfLensConfiguration(const std::string& initializationSequenceString)
{
    std::vector<std::string> initializationSequence = parseInitializationSequenceString(initializationSequenceString);

    InitializationSequenceAnalyzer initializationSequenceAnalyzer{std::move(initializationSequence)};

    initializationSequenceAnalyzer.executeSequence();

    return initializationSequenceAnalyzer.getFocusingPower();
}

}
}
}