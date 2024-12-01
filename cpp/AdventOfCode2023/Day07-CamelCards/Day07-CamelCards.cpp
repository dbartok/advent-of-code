#include "Day07-CamelCards.h"

#include "HandComparator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day07
{

struct PlayerState
{
    std::string hand;
    int bid;
};

PlayerState parseCamelCardLine(const std::string& camelCardsLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, camelCardsLine, boost::is_any_of(" "));

    return {std::move(tokens.at(0)), std::stoi(tokens.at(1))};
}

std::vector<PlayerState> parseCamelCardLines(const std::vector<std::string>& camelCardsLines)
{
    std::vector<PlayerState> playerStates;

    for (const auto& camelCardsLine : camelCardsLines)
    {
        PlayerState playerState = parseCamelCardLine(camelCardsLine);
        playerStates.push_back(std::move(playerState));
    }

    return playerStates;
}

int totalWinnings(const std::vector<std::string>& camelCardsLines, const HandComparator& handComparator)
{
    std::vector<PlayerState> playerStates = parseCamelCardLines(camelCardsLines);

    std::sort(playerStates.begin(), playerStates.end(), [&handComparator](const auto& lhs, const auto& rhs)
              {
                  return handComparator(lhs.hand, rhs.hand);
              });

    int totalWinnings = 0;
    for (int i = 0; i < playerStates.size(); ++i)
    {
        totalWinnings += (i + 1) * playerStates.at(i).bid;
    }
    return totalWinnings;
}

int totalWinnings(const std::vector<std::string>& camelCardsLines)
{
    return totalWinnings(camelCardsLines, HandComparator{});
}

int totalWinningsWithJokers(const std::vector<std::string>& camelCardsLines)
{
    return totalWinnings(camelCardsLines, HandComparator{'J'});
}

}
}
}