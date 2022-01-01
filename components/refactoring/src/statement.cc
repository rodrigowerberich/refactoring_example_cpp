#include "statement.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <algorithm>

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
 
    auto usd(int value) -> auto
    {
        auto result = std::stringstream();
        std::locale comma_locale(std::locale(), new comma_numpunct());
        result.imbue(comma_locale);
        result << std::fixed << std::setprecision(2.0) << std::setfill('0') << (static_cast<double>(value) / 100.0);
        return result.str();
    };

    class PerformanceWithExtraData: public Performance
    {
    public:
        PerformanceWithExtraData(): Performance{}{}
        PerformanceWithExtraData(const Performance& _performance, const Play& _play): Performance{_performance}, m_play{_play}, m_amount{0}{}
        const Play & play() const { return m_play; }
        int amount() const { return m_amount; }
        void setAmount(int newAmount) { m_amount = newAmount; }
    private:
        Play m_play;
        int m_amount;
    };


    class StatementData
    {
    public:
        using Performances=std::vector<PerformanceWithExtraData>;
        StatementData(const std::string& _customer, const Performances& _performances): m_customer{_customer}, m_performances{_performances}{}
        const std::string& customer() const {return m_customer; }
        const Performances& performances() const { return m_performances; }
    private:
        std::string m_customer;
        Performances m_performances;
    };

    auto amountFor(const PerformanceWithExtraData &aPerformance)
    {
        auto result = int(0);

        switch (aPerformance.play().type())
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

    auto volumeCreditsFor(const PerformanceWithExtraData& aPerformance) -> auto
    {
        auto result = int(0);
        result += std::max(aPerformance.audience() - 30, 0);
        if (Play::Type::Comedy == aPerformance.play().type())
            result += std::floor(static_cast<double>(aPerformance.audience()) / 5.0);
        return result;
    };

    auto totalVolumeCredits(const StatementData& data) -> auto
    {
        auto result = int(0);
        for (const auto &perf : data.performances())
        {
            result += volumeCreditsFor(perf);
        }
        return result;
    };

    auto totalAmount(const StatementData& data) -> auto
    {
        auto result = int(0);
        for (const auto &perf : data.performances())
        {
            result += perf.amount();
        }
        return result;
    };

    std::string renderPlainText(const StatementData& data, const Plays & plays)
    {

        auto result = std::stringstream();
        result << "Statement for " << data.customer() << std::endl;

        for (const auto &perf : data.performances())
        {
            // print line for this order
            result << " " << perf.play().name() << ": $" << usd(perf.amount()) << " (" << perf.audience() << " seats)" << std::endl;
        }

        result << "Amount owed is $" << usd(totalAmount(data)) << std::endl;
        result << "You earned " << totalVolumeCredits(data) << " credits" << std::endl;

        return result.str();
    }

    auto playFor(const Performance & aPerformance, const Plays &plays) -> const auto &
    {
        return plays.at(aPerformance.playId());
    };


    PerformanceWithExtraData enrichPerformance(const Performance& aPerformance, const Plays &plays)
    {
        PerformanceWithExtraData result
        {
            aPerformance,
            playFor(aPerformance, plays)
        };
        result.setAmount(amountFor(result));
        return result;
    }

    StatementData::Performances enrichPerformances(const Performances& performances, const Plays &plays)
    {
        StatementData::Performances result;
        result.reserve(performances.size());
        for(const auto& performance: performances)
        {
            result.push_back(enrichPerformance(performance, plays));
        }
        return result;
    }

    std::string statement(const Invoice &invoice, const Plays &plays)
    {
        auto statementData = StatementData 
        {
            invoice.customer(),
            enrichPerformances(invoice.performances(), plays)
        };
        return renderPlainText(statementData, plays);
    }

} // namespace TheaterBilling
