#pragma once

#include <string>

#include "performances.h"


namespace TheaterBilling
{

class Invoice{
public:
    Invoice(const std::string& _customer, const Performances& _performances): m_customer{_customer}, m_performances{_performances}{}
    Invoice(const std::string& _customer, Performances&& _performances): m_customer{_customer}, m_performances{std::move(_performances)}{}
    Invoice(std::string&& _customer, Performances&& _performances): m_customer{std::move(_customer)}, m_performances{std::move(_performances)}{}
    const std::string & customer() const { return m_customer; }
    const Performances& performance() const { return m_performances; }

private:
    std::string m_customer;
    Performances m_performances;
};

} // namespace TheaterBilling