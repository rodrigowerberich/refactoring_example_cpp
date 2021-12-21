#include "statement.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cmath>

namespace TheaterBilling
{

class comma_numpunct : public std::numpunct<char>
{
  protected:
    virtual char do_thousands_sep() const
    {
        return ',';
    }

    virtual std::string do_grouping() const
    {
        return "\03";
    }
};

    std::string statement(const Plays &plays, const Invoice &invoice)
    {
        auto totalAmount = int(0);
        auto volumeCredits = int(0);
        auto result = std::stringstream();
        result << "Statement for " << invoice.customer() << std::endl;
        auto format = [](double value) -> auto
        {
            auto result = std::stringstream();
            std::locale comma_locale(std::locale(), new comma_numpunct());
            result.imbue(comma_locale);
            result << std::fixed << std::setprecision(2.0) << std::setfill('0') << value;
            return result.str();
        };

        for (const auto &perf : invoice.performances())
        {
            const auto play = plays.at(perf.playId());
            auto thisAmount = int(0);

            switch (play.type())
            {
            case Play::Type::Tragedy:
            {
                thisAmount = 40000;
                if (perf.audience() > 30)
                {
                    thisAmount += 1000 * (perf.audience() - 30);
                }
                break;
            }
            case Play::Type::Comedy:
            {
                thisAmount = 30000;
                if (perf.audience() > 20)
                {
                    thisAmount += 10000 + 500 * (perf.audience() - 20);
                }
                thisAmount += 300 * perf.audience();
                break;
            }
            case Play::Type::Invalid:
                throw std::runtime_error("All performances need a valid play type.");
            default:
                throw std::runtime_error("Unsupported play type in invoice generation.");
            }

            // add volume credits
            volumeCredits+= std::max(perf.audience()-30, 0);
            // add extra credit for every ten comedy attendees
            if (Play::Type::Comedy == play.type()) volumeCredits +=  std::floor(static_cast<double>(perf.audience()) / 5.0);

            // print line for this order
            result << " " << play.name() << ": $" << format(static_cast<double>(thisAmount) / 100.0) << " (" << perf.audience() << " seats)" << std::endl;
            totalAmount += thisAmount; 
        }

        result << "Amount owed is $" << format(static_cast<double>(totalAmount) / 100.0) << std::endl;
        result << "You earned " << volumeCredits << " credits" << std::endl;

        return result.str();
    }

} // namespace TheaterBilling
