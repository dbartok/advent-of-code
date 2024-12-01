#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day02
{

enum class ROCK_PAPER_SCISSORS_HAND
{
    ROCK = 0,
    PAPER = 1,
    SCISSORS = 2,
};

enum class ROCK_PAPER_SCISSORS_ROUND_OUTCOME
{
    WIN,
    DRAW,
    LOSS,
};

class RockPaperScissorsRound
{
public:
    RockPaperScissorsRound(ROCK_PAPER_SCISSORS_HAND playerHand, ROCK_PAPER_SCISSORS_HAND opponentHand);

    int getPlayerScore() const;

    static ROCK_PAPER_SCISSORS_HAND getPlayerHandForDesiredOutcome(ROCK_PAPER_SCISSORS_HAND opponentHand, ROCK_PAPER_SCISSORS_ROUND_OUTCOME desiredOutcome);

private:
    int getSelectedShapeScore() const;
    int getOutcomeScore() const;
    ROCK_PAPER_SCISSORS_ROUND_OUTCOME getOutcome() const;

    static ROCK_PAPER_SCISSORS_HAND getPlayerHandForLoss(ROCK_PAPER_SCISSORS_HAND opponentHand);
    static ROCK_PAPER_SCISSORS_HAND getPlayerHandForWin(ROCK_PAPER_SCISSORS_HAND opponentHand);

    ROCK_PAPER_SCISSORS_HAND m_playerHand;
    ROCK_PAPER_SCISSORS_HAND m_opponentHand;
};

}
}
}
