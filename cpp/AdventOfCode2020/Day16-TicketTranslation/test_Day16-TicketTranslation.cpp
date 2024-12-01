#include "Day16-TicketTranslation.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day16;

TEST_CLASS(Day16TicketTranslation)
{
public:

    TEST_METHOD(ticketScanningErrorRate_SimpleTests)
    {
        std::vector<std::string> lines =
        {
            "class: 1-3 or 5-7",
            "row: 6-11 or 33-44",
            "seat: 13-40 or 45-50",
            "",
            "your ticket:",
            "7,1,14",
            "",
            "nearby tickets:",
            "7,3,47",
            "40,4,50",
            "55,2,20",
            "38,6,12"
        };

        Assert::AreEqual(71, CurrentDay::ticketScanningErrorRate(lines));
    }

    TEST_METHOD(ticketScanningErrorRate_SimpleTests)
    {
        std::vector<std::string> lines =
        {
            "departure class: 0-1 or 4-19",
            "departure row: 0-5 or 8-19",
            "seat: 0-13 or 16-19",
            "",
            "your ticket:",
            "11,12,13",
            "",
            "nearby tickets:",
            "3,9,18",
            "15,1,5",
            "5,14,9"
        };

        Assert::AreEqual(132ll, CurrentDay::departureValuesMultiplied(lines));
    }

};
