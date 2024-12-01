#include "Day02-RockPaperScissors.h"

#include "RockPaperScissorsRound.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const char PLAYER_ROCK_CHAR = 'X';
const char PLAYER_PAPER_CHAR = 'Y';
const char PLAYER_SCISSORS_CHAR = 'Z';
const char OUTCOME_LOSS_CHAR = 'X';
const char OUTCOME_DRAW_CHAR = 'Y';
const char OUTCOME_WIN_CHAR = 'Z';
const char OPPONENT_ROCK_CHAR = 'A';
const char OPPONENT_PAPER_CHAR = 'B';
const char OPPONENT_SCISSORS_CHAR = 'C';

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day02
{

ROCK_PAPER_SCISSORS_HAND parsePlayerHandChar(char playerHandChar)
{
    switch (playerHandChar)
    {
        case PLAYER_ROCK_CHAR:
            return ROCK_PAPER_SCISSORS_HAND::ROCK;
        case PLAYER_PAPER_CHAR:
            return ROCK_PAPER_SCISSORS_HAND::PAPER;
        case PLAYER_SCISSORS_CHAR:
            return ROCK_PAPER_SCISSORS_HAND::SCISSORS;
        default:
            throw std::runtime_error("Invalid player hand character: " + std::string{playerHandChar});
    }
}

ROCK_PAPER_SCISSORS_HAND parseOpponentHandChar(char opponentHandChar)
{
    switch (opponentHandChar)
    {
        case OPPONENT_ROCK_CHAR:
            return ROCK_PAPER_SCISSORS_HAND::ROCK;
        case OPPONENT_PAPER_CHAR:
            return ROCK_PAPER_SCISSORS_HAND::PAPER;
        case OPPONENT_SCISSORS_CHAR:
            return ROCK_PAPER_SCISSORS_HAND::SCISSORS;
        default:
            throw std::runtime_error("Invalid opponent hand character: " + std::string{opponentHandChar});
    }
}

ROCK_PAPER_SCISSORS_ROUND_OUTCOME parseDesiredOutcomeChar(char desiredOutcomeChar)
{
    switch (desiredOutcomeChar)
    {
        case OUTCOME_LOSS_CHAR:
            return ROCK_PAPER_SCISSORS_ROUND_OUTCOME::LOSS;
        case OUTCOME_DRAW_CHAR:
            return ROCK_PAPER_SCISSORS_ROUND_OUTCOME::DRAW;
        case OUTCOME_WIN_CHAR:
            return ROCK_PAPER_SCISSORS_ROUND_OUTCOME::WIN;
        default:
            throw std::runtime_error("Invalid desired outcome character: " + std::string{desiredOutcomeChar});
    }
}


RockPaperScissorsRound parseStrategyGuideLine(const std::string& strategyGuideLine)
{
    ROCK_PAPER_SCISSORS_HAND playerHand = parsePlayerHandChar(strategyGuideLine.at(2));
    ROCK_PAPER_SCISSORS_HAND opponentHand = parseOpponentHandChar(strategyGuideLine.at(0));

    return RockPaperScissorsRound{playerHand, opponentHand};
}

RockPaperScissorsRound parseStrategyGuideLineAccordingToElfInstructions(const std::string& strategyGuideLine)
{
    ROCK_PAPER_SCISSORS_HAND opponentHand = parseOpponentHandChar(strategyGuideLine.at(0));
    ROCK_PAPER_SCISSORS_ROUND_OUTCOME desiredOutcome = parseDesiredOutcomeChar(strategyGuideLine.at(2));

    ROCK_PAPER_SCISSORS_HAND playerHand = RockPaperScissorsRound::getPlayerHandForDesiredOutcome(opponentHand, desiredOutcome);

    return RockPaperScissorsRound{playerHand, opponentHand};
}

std::vector<RockPaperScissorsRound> parseStrategyGuideLines(const std::vector<std::string>& strategyGuideLines)
{
    std::vector<RockPaperScissorsRound> rockPaperScissorsRounds;

    for (const auto& strategyGuideLine : strategyGuideLines)
    {
        RockPaperScissorsRound rockPaperScissorsRound = parseStrategyGuideLine(strategyGuideLine);
        rockPaperScissorsRounds.push_back(std::move(rockPaperScissorsRound));
    }

    return rockPaperScissorsRounds;
}

std::vector<RockPaperScissorsRound> parseStrategyGuideLinesAccordingToElfInstructions(const std::vector<std::string>& strategyGuideLines)
{
    std::vector<RockPaperScissorsRound> rockPaperScissorsRounds;

    for (const auto& strategyGuideLine : strategyGuideLines)
    {
        RockPaperScissorsRound rockPaperScissorsRound = parseStrategyGuideLineAccordingToElfInstructions(strategyGuideLine);
        rockPaperScissorsRounds.push_back(std::move(rockPaperScissorsRound));
    }

    return rockPaperScissorsRounds;
}

int totalScoreAccordingToStrategyGuide(const std::vector<std::string>& strategyGuideLines)
{
    std::vector<RockPaperScissorsRound> rockPaperScissorsRounds = parseStrategyGuideLines(strategyGuideLines);

    return std::accumulate(rockPaperScissorsRounds.cbegin(), rockPaperScissorsRounds.cend(), 0, [](const auto& acc, const auto& round) {return acc + round.getPlayerScore(); });
}

int totalScoreAccordingToElfInstructions(const std::vector<std::string>& strategyGuideLines)
{
    std::vector<RockPaperScissorsRound> rockPaperScissorsRounds = parseStrategyGuideLinesAccordingToElfInstructions(strategyGuideLines);

    return std::accumulate(rockPaperScissorsRounds.cbegin(), rockPaperScissorsRounds.cend(), 0, [](const auto& acc, const auto& round) {return acc + round.getPlayerScore(); });
}

}
}
}