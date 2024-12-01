#include "TicketDecoder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
#include <algorithm>
#include <cassert>
#include <iterator>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day16
{

TicketFieldValidator::TicketFieldValidator(std::vector<Range> ranges)
    : m_ranges{std::move(ranges)}
{

}

bool TicketFieldValidator::isValid(TicketValue ticketValue) const
{
    for (const auto& range : m_ranges)
    {
        if (range.first <= ticketValue && ticketValue <= range.second)
        {
            return true;
        }
    }

    return false;
}

TicketValueClassifier::TicketValueClassifier(TicketFieldNameToValidator ticketFieldNameToValidator)
    : m_ticketFieldNameToValidator{std::move(ticketFieldNameToValidator)}
{

}

std::vector<std::string> TicketValueClassifier::getPossibleTicketFieldNames(TicketValue ticketValue) const
{
    std::vector<std::string> possibleTicketFieldNames;

    for (const auto& fieldNameAndValidator : m_ticketFieldNameToValidator)
    {
        if (fieldNameAndValidator.second.isValid(ticketValue))
        {
            possibleTicketFieldNames.push_back(fieldNameAndValidator.first);
        }
    }

    return possibleTicketFieldNames;
}

TicketDecoder::TicketDecoder(TicketValueClassifier ticketValueClassifier, Ticket ownTicket, std::vector<Ticket> nearbyTickets)
    : m_ticketValueClassifier{std::move(ticketValueClassifier)}
    , m_ownTicket{std::move(ownTicket)}
    , m_nearbyTickets{std::move(nearbyTickets)}
    , m_numTicketFields{m_ownTicket.size()}
    , m_ticketFieldIndexToPossibleNames(m_numTicketFields)
{

}

void TicketDecoder::discardInvalidTickets()
{
    std::vector<Ticket> validNearbyTickets;

    std::copy_if(m_nearbyTickets.cbegin(), m_nearbyTickets.cend(), std::back_inserter(validNearbyTickets), [this](const auto& ticket)
                    {
                        return !std::any_of(ticket.cbegin(), ticket.cend(), [this](const auto& ticketValue)
                                            {
                                                return this->m_ticketValueClassifier.getPossibleTicketFieldNames(ticketValue).empty();
                                            });
                    });

    m_nearbyTickets = validNearbyTickets;
}

void TicketDecoder::decode()
{
    determineInitialPossibilities();
    derivePossibilitiesBasedOnOtherPossibilities();
}

int TicketDecoder::getTicketScanningErrorRate() const
{
    return std::accumulate(m_nearbyTickets.cbegin(), m_nearbyTickets.cend(), 0, [this](int acc, const auto& ticket)
                            {
                                return acc + std::accumulate(ticket.cbegin(), ticket.cend(), 0, [this](int ticketAcc, const auto& ticketValue)
                                                            {
                                                                return ticketAcc + (this->m_ticketValueClassifier.getPossibleTicketFieldNames(ticketValue).empty() ? ticketValue : 0);
                                                            });
                            });
}

int64_t TicketDecoder::getDepartureValuesMultiplied() const
{
    int64_t departureValuesMultiplied = 1;

    for (size_t i = 0; i < m_numTicketFields; ++i)
    {
        const auto& possibleNames = m_ticketFieldIndexToPossibleNames.at(i);
        assert(possibleNames.size() == 1);
        const auto& name = *possibleNames.cbegin();
        if (name.rfind("departure", 0) == 0)
        {
            departureValuesMultiplied *= m_ownTicket.at(i);
        }
    }

    return departureValuesMultiplied;
}

void TicketDecoder::determineInitialPossibilities()
{
    for (size_t fieldIndex = 0; fieldIndex < m_numTicketFields; ++fieldIndex)
    {
        std::vector<std::string> possibleNamesBasedOnOwnTicket = m_ticketValueClassifier.getPossibleTicketFieldNames(m_ownTicket.at(fieldIndex));
        m_ticketFieldIndexToPossibleNames.at(fieldIndex).insert(std::make_move_iterator(possibleNamesBasedOnOwnTicket.begin()),
                                                                std::make_move_iterator(possibleNamesBasedOnOwnTicket.end()));

        constrainPossibilitiesForFieldBasedOnNearbyTickets(fieldIndex);
    }
}

void TicketDecoder::constrainPossibilitiesForFieldBasedOnNearbyTickets(size_t fieldIndex)
{
    for (const auto& nearbyTicket : m_nearbyTickets)
    {
        const TicketValue ticketValue = nearbyTicket.at(fieldIndex);
        std::vector<std::string> possibleNamesBasedOnNearbyTicket = m_ticketValueClassifier.getPossibleTicketFieldNames(ticketValue);
        std::unordered_set<std::string> possibleNamesBasedOnNearbyTicketSet{std::make_move_iterator(possibleNamesBasedOnNearbyTicket.begin()),
                                                                            std::make_move_iterator(possibleNamesBasedOnNearbyTicket.end())};

        auto& possibleNames = m_ticketFieldIndexToPossibleNames.at(fieldIndex);
        std::unordered_set<std::string> constrainedPossibleNames{possibleNames};

        for (const auto& possibleName : possibleNames)
        {
            if (possibleNamesBasedOnNearbyTicketSet.find(possibleName) == possibleNamesBasedOnNearbyTicketSet.cend())
            {
                constrainedPossibleNames.erase(possibleName);
            }
        }

        possibleNames = constrainedPossibleNames;
    }
}

void TicketDecoder::derivePossibilitiesBasedOnOtherPossibilities()
{
    std::unordered_set<size_t> finalizedIndices;

    while (finalizedIndices.size() != m_numTicketFields)
    {
        for (size_t i = 0; i < m_numTicketFields; ++i)
        {
            if (finalizedIndices.find(i) == finalizedIndices.cend() && m_ticketFieldIndexToPossibleNames.at(i).size() == 1)
            {
                finalizedIndices.insert(i);
                eliminatePossibilitiesAtOtherIndicesBasedOnFinalizedIndex(i);
                break;
            }
        }
    }
}

void TicketDecoder::eliminatePossibilitiesAtOtherIndicesBasedOnFinalizedIndex(size_t finalizedIndex)
{
    const std::string& onlyPossibleName = *m_ticketFieldIndexToPossibleNames.at(finalizedIndex).cbegin();
    for (size_t i = 0; i < m_numTicketFields; ++i)
    {
        if (i != finalizedIndex)
        {
            m_ticketFieldIndexToPossibleNames.at(i).erase(onlyPossibleName);
        }
    }
}

}
}
}
