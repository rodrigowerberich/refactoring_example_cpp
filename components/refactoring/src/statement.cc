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
        auto usd = [](int value) -> auto
        {
            auto result = std::stringstream();
            std::locale comma_locale(std::locale(), new comma_numpunct());
            result.imbue(comma_locale);
            result << std::fixed << std::setprecision(2.0) << std::setfill('0') << (static_cast<double>(value) / 100.0);
            return result.str();
        };
        auto playFor = [&plays](const auto &aPerformance) -> const auto &
        {
            return plays.at(aPerformance.playId());
        };
        auto amountFor = [&playFor](const Performance &aPerformance)
        {
            auto result = int(0);

            switch (playFor(aPerformance).type())
            {
            case Play::Type::Tragedy:
            {
                result = 40000;
                if (aPerformance.audience() > 30)
                {
                    result += 1000 * (aPerformance.audience() - 30);
                }
                break;
            }
            case Play::Type::Comedy:
            {
                result = 30000;
                if (aPerformance.audience() > 20)
                {
                    result += 10000 + 500 * (aPerformance.audience() - 20);
                }
                result += 300 * aPerformance.audience();
                break;
            }
            case Play::Type::Invalid:
                throw std::runtime_error("All performances need a valid play type.");
            default:
                throw std::runtime_error("Unsupported play type in invoice generation.");
            }

            return result;
        };

        auto volumeCreditsFor = [&playFor](const auto& aPerformance) -> auto
        {
            auto result = int(0);
            result += std::max(aPerformance.audience() - 30, 0);
            if (Play::Type::Comedy == playFor(aPerformance).type())
                result += std::floor(static_cast<double>(aPerformance.audience()) / 5.0);
            return result;
        };

        auto totalAmount = int(0);
        auto volumeCredits = int(0);
        auto result = std::stringstream();
        result << "Statement for " << invoice.customer() << std::endl;

        for (const auto &perf : invoice.performances())
        {
            volumeCredits += volumeCreditsFor(perf);

            // print line for this order
            result << " " << playFor(perf).name() << ": $" << usd(amountFor(perf)) << " (" << perf.audience() << " seats)" << std::endl;
            totalAmount += amountFor(perf);
        }

        result << "Amount owed is $" << usd(totalAmount) << std::endl;
        result << "You earned " << volumeCredits << " credits" << std::endl;

        return result.str();
    }

} // namespace TheaterBilling
