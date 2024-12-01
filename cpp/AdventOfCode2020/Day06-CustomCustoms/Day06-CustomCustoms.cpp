#include "Day06-CustomCustoms.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <unordered_set>
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day06
{

using GroupAnswerTextSection = std::vector<std::string>;

struct GroupAnswer
{
    GroupAnswerTextSection answerSequences;

    int getUnionOfYesAnswers() const
    {
        std::unordered_set<char> answerUnion;
        auto allAnswers = boost::join(answerSequences, "");

        for (char answer : allAnswers)
        {
            answerUnion.insert(answer);
        }

        return answerUnion.size();
    }

    int getIntersectionOfYesAnswers() const
    {
        std::string firstAnswerSequenceSorted = answerSequences.front();
        std::sort(firstAnswerSequenceSorted.begin(), firstAnswerSequenceSorted.end());
        std::string answerIntersection{firstAnswerSequenceSorted.cbegin(), firstAnswerSequenceSorted.cend()};

        for (auto answerSequenceIter = std::next(answerSequences.cbegin()); answerSequenceIter != answerSequences.cend(); ++answerSequenceIter)
        {
            std::string currentAnswerSequenceSorted = *answerSequenceIter;
            std::sort(currentAnswerSequenceSorted.begin(), currentAnswerSequenceSorted.end());
            std::string newAnswerIntersection;
            std::set_intersection(answerIntersection.cbegin(), answerIntersection.cend(),
                                  currentAnswerSequenceSorted.cbegin(), currentAnswerSequenceSorted.cend(),
                                  std::back_inserter(newAnswerIntersection));

            answerIntersection = std::move(newAnswerIntersection);
        }

        return answerIntersection.size();
    }
};

std::vector<GroupAnswer> parseGroupAnswers(const std::vector<std::string>& lines)
{
    std::vector<GroupAnswerTextSection> groupAnswerTextSections;
    boost::split(groupAnswerTextSections, lines, [](const auto& elem) {return elem.empty(); });

    std::vector<GroupAnswer> groupAnswers;
    for (auto& groupAnswerTextSection : groupAnswerTextSections)
    {
        GroupAnswer groupAnswer{std::move(groupAnswerTextSection)};
        groupAnswers.push_back(std::move(groupAnswer));
    }

    return groupAnswers;
}

int sumAnyoneAnsweredYes(const std::vector<std::string>& lines)
{
    std::vector<GroupAnswer> groupAnswers = parseGroupAnswers(lines);
    return std::accumulate(groupAnswers.cbegin(), groupAnswers.cend(), 0, [](int acc, const auto& groupAnswer)
                           {
                               return acc + groupAnswer.getUnionOfYesAnswers();
                           });
}

int sumEveryoneAnsweredYes(const std::vector<std::string>& lines)
{
    std::vector<GroupAnswer> groupAnswers = parseGroupAnswers(lines);
    return std::accumulate(groupAnswers.cbegin(), groupAnswers.cend(), 0, [](int acc, const auto& groupAnswer)
                           {
                               return acc + groupAnswer.getIntersectionOfYesAnswers();
                           });
}


}
}
}
