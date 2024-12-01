#include "Day01-Trebuchet.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const char* DIGITS = "0123456789";

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day01
{

int getCalibrationValue(const std::string& calibrationDocumentLine)
{
    const size_t firstDigitIndex = calibrationDocumentLine.find_first_of(DIGITS);
    const size_t lastDigitIndex = calibrationDocumentLine.find_last_of(DIGITS);

    std::string calibrationValueString;
    calibrationValueString += calibrationDocumentLine.at(firstDigitIndex);
    calibrationValueString += calibrationDocumentLine.at(lastDigitIndex);

    return std::stoi(calibrationValueString);
}

int digitOrSpelledOutDigitToInt(const std::string& digitOrSpelledOutDigit)
{
    if (digitOrSpelledOutDigit == "zero")
    {
        return 0;
    }
    else if (digitOrSpelledOutDigit == "one")
    {
        return 1;
    }
    else if (digitOrSpelledOutDigit == "two")
    {
        return 2;
    }
    else if (digitOrSpelledOutDigit == "three")
    {
        return 3;
    }
    else if (digitOrSpelledOutDigit == "four")
    {
        return 4;
    }
    else if (digitOrSpelledOutDigit == "five")
    {
        return 5;
    }
    else if (digitOrSpelledOutDigit == "six")
    {
        return 6;
    }
    else if (digitOrSpelledOutDigit == "seven")
    {
        return 7;
    }
    else if (digitOrSpelledOutDigit == "eight")
    {
        return 8;
    }
    else if (digitOrSpelledOutDigit == "nine")
    {
        return 9;
    }
    else
    {
        return std::stoi(digitOrSpelledOutDigit);
    }
}

int getCalibrationValueSpelledOutWithLetters(const std::string& calibrationDocumentLine)
{
    const std::string numbersCapturingRegex(R"(([0-9]|zero|one|two|three|four|five|six|seven|eight|nine))");
    std::smatch matchResults;

    std::regex_search(calibrationDocumentLine, matchResults, std::regex{numbersCapturingRegex});
    const int firstDigit = digitOrSpelledOutDigitToInt(matchResults[1]);

    std::regex_search(calibrationDocumentLine, matchResults, std::regex{"^.*" + numbersCapturingRegex});
    const int lastDigit = digitOrSpelledOutDigitToInt(matchResults[1]);

    return 10 * firstDigit + lastDigit;
}

int sumOfAllCalibrationValues(const std::vector<std::string>& calibrationDocumentLines)
{
    return std::accumulate(calibrationDocumentLines.cbegin(), calibrationDocumentLines.cend(), 0, [](int acc, const std::string& line)
                           {
                               return acc + getCalibrationValue(line);
                           });
}

int sumOfAllCalibrationValuesSpelledOutWithLetters(const std::vector<std::string>& calibrationDocumentLines)
{
    return std::accumulate(calibrationDocumentLines.cbegin(), calibrationDocumentLines.cend(), 0, [](int acc, const std::string& line)
                           {
                               return acc + getCalibrationValueSpelledOutWithLetters(line);
                           });
}

}
}
}