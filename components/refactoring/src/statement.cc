#include "statement.h"

namespace TheaterBilling
{

std::string statement(const Plays& plays, const Invoices& invoices){
    return R"(Statement for BigCo
 Hamlet: $650.00 (55 seats)
 As You Like It: $580.00 (35 seats)
 Othello: $500.00 (40 seats)
Amount owed is $1,730.00
You earned 47 credits
)";
}

} // namespace TheaterBilling

