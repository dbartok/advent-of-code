#include "Day16-TicketTranslation.h"

#include "TicketDecoder.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day16
{

using TextSection = std::vector<std::string>;

Range parseRange(const std::string& rangeString)
{
    std::vector<std::string> tokens;
    boost::split(tokens, rangeString, boost::is_any_of("-"));

    return Range{std::stoi(tokens.at(0)), std::stoi(tokens.at(1))};
}

std::vector<Range> parseRanges(const std::string& rangesString)
{
    std::vector<std::string> tokens;
    boost::split(tokens, rangesString, boost::is_any_of("or "), boost::token_compress_on);

    std::vector<Range> ranges;

    for (const auto& token : tokens)
    {
        Range range = parseRange(token);
        ranges.push_back(std::move(range));
    }

    return ranges;
}

TicketFieldNameToValidator parseTicketFieldNameToValidator(const TextSection& rulesSection)
{
    TicketFieldNameToValidator ticketFieldNameToValidator;

    for (const auto& line : rulesSection)
    {
        const size_t colonPosition = line.find(':');
        std::string name = line.substr(0, colonPosition);
        std::vector<Range> ranges = parseRanges(line.substr(colonPosition + 2));

        TicketFieldValidator ticketFieldValidator{ranges};

        ticketFieldNameToValidator.emplace(name, TicketFieldValidator{std::move(ranges)});
    }

    return ticketFieldNameToValidator;
}

Ticket parseTicket(const std::string& ticketString)
{
    Ticket outputTicket;
    Utils::splitStringIntoTypedVector(ticketString, outputTicket, ',');
    return outputTicket;
}

Ticket parseOwnTicket(const TextSection& rulesSection)
{
    return parseTicket(rulesSection.at(1));
}

std::vector<Ticket> parseNearbyTickets(const TextSection& rulesSection)
{
    std::vector<Ticket> tickets;

    for (auto ticketStringIter = std::next(rulesSection.cbegin()); ticketStringIter != rulesSection.cend(); ++ticketStringIter)
    {
        Ticket ticket = parseTicket(*ticketStringIter);
        tickets.push_back(std::move(ticket));
    }

    return tickets;
}

TicketDecoder createTicketDecoder(const std::vector<std::string>& noteLines)
{
    std::vector<TextSection> textSections;
    boost::split(textSections, noteLines, [](const auto& elem) {return elem.empty(); });

    TicketFieldNameToValidator ticketFieldNameToValidator = parseTicketFieldNameToValidator(textSections.at(0));
    TicketValueClassifier ticketValueClassifier{std::move(ticketFieldNameToValidator)};

    Ticket ownTicket = parseOwnTicket(textSections.at(1));

    std::vector<Ticket> nearbyTickets = parseNearbyTickets(textSections.at(2));

    return TicketDecoder{std::move(ticketValueClassifier), std::move(ownTicket), std::move(nearbyTickets)};
}

int ticketScanningErrorRate(const std::vector<std::string>& noteLines)
{
    TicketDecoder ticketDecoder = createTicketDecoder(noteLines);
    return ticketDecoder.getTicketScanningErrorRate();
}

int64_t departureValuesMultiplied(const std::vector<std::string>& noteLines)
{
    TicketDecoder ticketDecoder = createTicketDecoder(noteLines);
    ticketDecoder.discardInvalidTickets();
    ticketDecoder.decode();
    return ticketDecoder.getDepartureValuesMultiplied();
}

}
}
}
