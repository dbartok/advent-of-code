#include "Day20-PulsePropagation.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day20;

TEST_CLASS(Day20PulsePropagation)
{
public:

    TEST_METHOD(numLowAndHighPulsesMultipliedTogether_StatelessConfiguration)
    {
        const std::vector<std::string> lines =
        {
            "broadcaster -> a, b, c",
            "%a -> b",
            "%b -> c",
            "%c -> inv",
            "&inv -> a"
        };

        Assert::AreEqual(32000000, CurrentDay::numLowAndHighPulsesMultipliedTogether(lines));
    }

    TEST_METHOD(numLowAndHighPulsesMultipliedTogether_StatefulConfiguration)
    {
        const std::vector<std::string> lines =
        {
            "broadcaster -> a",
            "%a -> inv, con",
            "&inv -> b",
            "%b -> con",
            "&con -> output"
        };

        Assert::AreEqual(11687500, CurrentDay::numLowAndHighPulsesMultipliedTogether(lines));
    }

    TEST_METHOD(fewestNumButtonPressesToDeliverLowPulseToRx_RealInput)
    {
        const std::vector<std::string> lines =
        {
            "%qx -> gz",
            "%tr -> rm",
            "%qr -> kx, jm",
            "%gj -> tx, rj",
            "%lc -> hr",
            "&kx -> zs, br, jd, bj, vg",
            "&kd -> rg",
            "%rm -> pf, ml",
            "%tg -> tq, cp",
            "%cp -> tp, tq",
            "%sx -> qc, pf",
            "&zf -> rg",
            "%jz -> kx, pt",
            "%dt -> tg, tq",
            "%xv -> rj",
            "%vz -> rj, xv",
            "%vn -> vv, tq",
            "%hl -> xt",
            "%qc -> pf",
            "%br -> jz",
            "broadcaster -> sr, cg, dt, zs",
            "%sk -> kx, qr",
            "%xq -> dj",
            "&vg -> rg",
            "%zd -> pf, lc",
            "%hr -> pm",
            "%cg -> qx, rj",
            "%tx -> vz, rj",
            "%qf -> sb",
            "&rj -> gs, sb, qx, qf, gz, hl, cg",
            "%rb -> lz",
            "%ml -> pf, xq",
            "%bj -> jd",
            "&gs -> rg",
            "%sr -> pf, zd",
            "%sb -> gj",
            "&tq -> tp, rb, dt, kd, zt",
            "%tp -> dm",
            "%vv -> tq",
            "%pm -> tr",
            "%dj -> pf, sx",
            "%lz -> vn, tq",
            "%jd -> lx",
            "%qn -> tq, rb",
            "%zs -> kx, bj",
            "&rg -> rx",
            "%pt -> cb, kx",
            "%xt -> ns, rj",
            "%gz -> hl",
            "%zt -> qn",
            "%jm -> kx",
            "%vp -> br, kx",
            "&pf -> tr, hr, zf, sr, xq, pm, lc",
            "%gp -> tq, zt",
            "%dm -> tq, gp",
            "%lx -> kx, vp",
            "%ns -> qf, rj",
            "%cb -> sk, kx"
        };

        Assert::AreEqual(224602953547789ll, CurrentDay::fewestNumButtonPressesToDeliverLowPulseToRx(lines));
    }

};
