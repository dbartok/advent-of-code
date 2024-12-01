#include "Day09-MirageMaintenance.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day09
{

using History = std::vector<int>;

History parseHistoryLine(const std::string& historyLine)
{
    History history;
    AdventOfCode::Utils::splitStringIntoTypedVector(historyLine, history);
    return history;
}

std::vector<History> parseHistoryLines(const std::vector<std::string>& historyLines)
{
    std::vector<History> histories;

    for (const auto& historyLine : historyLines)
    {
        History history = parseHistoryLine(historyLine);
        histories.push_back(std::move(history));
    }

    return histories;
}

History getDifferentialSequence(const History& history)
{
    History differentialSequence;

    for (int i = 0; i < history.size() - 1; ++i)
    {
        const int differential = history.at(i + 1) - history.at(i);
        differentialSequence.push_back(differential);
    }

    return differentialSequence;
}

int extrapolate(const History& history)
{
    std::vector<History> differentialSequences{history};

    while (!std::all_of(differentialSequences.back().cbegin(), differentialSequences.back().cend(), [](const int n) { return n == 0; }))
    {
        History newDifferentialSequence = getDifferentialSequence(differentialSequences.back());
        differentialSequences.push_back(std::move(newDifferentialSequence));
    }

    for (auto differentialSequenceIter = differentialSequences.rbegin() + 1; differentialSequenceIter != differentialSequences.rend(); ++differentialSequenceIter)
    {
        const auto& sequenceWithExtrapolationInfo = *std::prev(differentialSequenceIter);
        auto& sequenceToExtrapolate = *differentialSequenceIter;

        const int extrapolatedValue = sequenceWithExtrapolationInfo.back() + sequenceToExtrapolate.back();
        sequenceToExtrapolate.push_back(extrapolatedValue);
    }

    return differentialSequences.front().back();
}

int sumOfExtrapolatedValues(const std::vector<History>& histories)
{
    int sumOfForwardExtrapolatedValues = 0;

    for (const auto& history : histories)
    {
        const int extrapolatedValue = extrapolate(history);
        sumOfForwardExtrapolatedValues += extrapolatedValue;
    }

    return sumOfForwardExtrapolatedValues;
}

int sumOfForwardsExtrapolatedValues(const std::vector<std::string>& historyLines)
{
    std::vector<History> histories = parseHistoryLines(historyLines);
    return sumOfExtrapolatedValues(histories);
}

int sumOfBackwardsExtrapolatedValues(const std::vector<std::string>& historyLines)
{
    std::vector<History> histories = parseHistoryLines(historyLines);

    std::for_each(histories.begin(), histories.end(), [](auto& history)
                  {
                      std::reverse(history.begin(), history.end());
                  });

    return sumOfExtrapolatedValues(histories);
}

}
}
}