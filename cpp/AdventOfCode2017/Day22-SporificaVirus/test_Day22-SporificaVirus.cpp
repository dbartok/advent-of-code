#include "Day22-SporificaVirus.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day22;

TEST_CLASS(Day22SporificaVirus)
{
public:

    TEST_METHOD(basicVirusInfectingBursts_SimpleTests)
    {
        Assert::AreEqual(5u, CurrentDay::basicVirusInfectingBursts(m_initialVirusPosLines, 7u));
        Assert::AreEqual(41u, CurrentDay::basicVirusInfectingBursts(m_initialVirusPosLines, 70u));
        Assert::AreEqual(5587u, CurrentDay::basicVirusInfectingBursts(m_initialVirusPosLines));
    }

    TEST_METHOD(evolvedVirusInfectingBursts_SimpleTests)
    {
        Assert::AreEqual(26u, CurrentDay::evolvedVirusInfectingBursts(m_initialVirusPosLines, 100u));

        // Runs slow in Debug (about two minutes)
        //Assert::AreEqual(2511944u, CurrentDay::evolvedVirusInfectingBursts(m_initialVirusPosLines));
    }

private:
    const std::vector<std::string> m_initialVirusPosLines =
    {
        "..#",
        "#..",
        "..."
    };

};
