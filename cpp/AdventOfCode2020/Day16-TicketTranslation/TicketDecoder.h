#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <unordered_map>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day16
{

using TicketValue = int;
using Ticket = std::vector<TicketValue>;
using Range = std::pair<TicketValue, TicketValue>;

class TicketFieldValidator;
using TicketFieldNameToValidator = std::unordered_map<std::string, TicketFieldValidator>;

class TicketFieldValidator
{
public:
    TicketFieldValidator(std::vector<Range> ranges);

    bool isValid(TicketValue ticketValue) const;

private:
    std::vector<Range> m_ranges;
};

class TicketValueClassifier
{
public:
    TicketValueClassifier(TicketFieldNameToValidator ticketFieldNameToValidator);

    std::vector<std::string> getPossibleTicketFieldNames(TicketValue ticketValue) const;

private:
    TicketFieldNameToValidator m_ticketFieldNameToValidator;
};

class TicketDecoder
{
public:
    TicketDecoder(TicketValueClassifier ticketValueClassifier, Ticket ownTicket, std::vector<Ticket> nearbyTickets);

    void discardInvalidTickets();
    void decode();

    int getTicketScanningErrorRate() const;
    int64_t getDepartureValuesMultiplied() const;

private:
    TicketValueClassifier m_ticketValueClassifier;
    Ticket m_ownTicket;
    std::vector<Ticket> m_nearbyTickets;

    std::vector<Ticket> m_allTickets;
    size_t m_numTicketFields;

    using TicketFieldNameSet = std::unordered_set<std::string>;
    std::vector<TicketFieldNameSet> m_ticketFieldIndexToPossibleNames;

    void determineInitialPossibilities();
    void constrainPossibilitiesForFieldBasedOnNearbyTickets(size_t fieldIndex);
    void derivePossibilitiesBasedOnOtherPossibilities();
    void eliminatePossibilitiesAtOtherIndicesBasedOnFinalizedIndex(size_t finalizedIndex);
};

}
}
}
