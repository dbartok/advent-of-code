#include "RockPaperScissorsRound.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stdexcept>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int NUM_SHAPES = 3;
const int SCORE_ROCK = 1;
const int SCORE_PAPER = 2;
const int SCORE_SCISSORS = 3;
const int SCORE_WIN = 6;
const int SCORE_DRAW = 3;
const int SCORE_LOSS = 0;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day02
{

RockPaperScissorsRound::RockPaperScissorsRound(ROCK_PAPER_SCISSORS_HAND playerHand, ROCK_PAPER_SCISSORS_HAND opponentHand)
    : m_playerHand(playerHand)
    , m_opponentHand(opponentHand)
{

}

int RockPaperScissorsRound::getPlayerScore() const
{
    auto s = getSelectedShapeScore() + getOutcomeScore();
    return s;
}

ROCK_PAPER_SCISSORS_HAND RockPaperScissorsRound::getPlayerHandForDesiredOutcome(ROCK_PAPER_SCISSORS_HAND opponentHand, ROCK_PAPER_SCISSORS_ROUND_OUTCOME desiredOutcome)
{
    switch (desiredOutcome)
    {
        case ROCK_PAPER_SCISSORS_ROUND_OUTCOME::LOSS:
            return getPlayerHandForLoss(opponentHand);
        case ROCK_PAPER_SCISSORS_ROUND_OUTCOME::DRAW:
            return opponentHand;
        case ROCK_PAPER_SCISSORS_ROUND_OUTCOME::WIN:
            return getPlayerHandForWin(opponentHand);
        default:
            throw std::runtime_error("Invalid desired outcome: " + std::to_string(static_cast<int>(desiredOutcome)));
    }
}

int RockPaperScissorsRound::getSelectedShapeScore() const
{
    switch (m_playerHand)
    {
        case ROCK_PAPER_SCISSORS_HAND::ROCK:
            return SCORE_ROCK;
        case ROCK_PAPER_SCISSORS_HAND::PAPER:
            return SCORE_PAPER;
        case ROCK_PAPER_SCISSORS_HAND::SCISSORS:
            return SCORE_SCISSORS;
        default:
            throw std::runtime_error("Invalid player hand: " + std::to_string(static_cast<int>(m_playerHand)));
    }
}

int RockPaperScissorsRound::getOutcomeScore() const
{
    const ROCK_PAPER_SCISSORS_ROUND_OUTCOME outcome = getOutcome();

    switch (outcome)
    {
        case ROCK_PAPER_SCISSORS_ROUND_OUTCOME::LOSS:
            return SCORE_LOSS;
        case ROCK_PAPER_SCISSORS_ROUND_OUTCOME::DRAW:
            return SCORE_DRAW;
        case ROCK_PAPER_SCISSORS_ROUND_OUTCOME::WIN:
            return SCORE_WIN;
        default:
            throw std::runtime_error("Invalid outcome: " + std::to_string(static_cast<int>(outcome)));
    }
}

ROCK_PAPER_SCISSORS_ROUND_OUTCOME RockPaperScissorsRound::getOutcome() const
{
    const ROCK_PAPER_SCISSORS_HAND handThatBeatsOpponentHand = getPlayerHandForWin(m_opponentHand);

    if (m_playerHand == handThatBeatsOpponentHand)
    {
        return ROCK_PAPER_SCISSORS_ROUND_OUTCOME::WIN;
    }

    if (m_opponentHand == m_playerHand)
    {
        return ROCK_PAPER_SCISSORS_ROUND_OUTCOME::DRAW;
    }

    return ROCK_PAPER_SCISSORS_ROUND_OUTCOME::LOSS;
}

ROCK_PAPER_SCISSORS_HAND RockPaperScissorsRound::getPlayerHandForLoss(ROCK_PAPER_SCISSORS_HAND opponentHand)
{
    return static_cast<ROCK_PAPER_SCISSORS_HAND>((static_cast<int>(opponentHand) + NUM_SHAPES - 1) % NUM_SHAPES);
}

ROCK_PAPER_SCISSORS_HAND RockPaperScissorsRound::getPlayerHandForWin(ROCK_PAPER_SCISSORS_HAND opponentHand)
{
    return static_cast<ROCK_PAPER_SCISSORS_HAND>((static_cast<int>(opponentHand) + 1) % NUM_SHAPES);
}

}
}
}
