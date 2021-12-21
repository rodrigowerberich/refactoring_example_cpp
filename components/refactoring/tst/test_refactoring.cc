#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <map>
#include <tuple>

#include "statement.h"

using ::testing::StrEq;
using namespace TheaterBilling;

std::tuple<Plays, Invoices> createTestData(){
    auto plays = Plays();
    plays["hamlet"] = Play("Hamlet", Play::Type::Tragedy);
    plays["as-like"] = Play("As You Like It", Play::Type::Comedy);
    plays["othello"] = Play("Othello", Play::Type::Tragedy);

    auto invoices = Invoices();
    return {plays, invoices};
}

TEST(RefactoringTst, DummyTest) {
    auto [plays, invoices] = createTestData();

    EXPECT_THAT(statement(plays, invoices), StrEq(
R"(Statement for BigCo
 Hamlet: $650.00 (55 seats)
 As You Like It: $580.00 (35 seats)
 Othello: $500.00 (40 seats)
Amount owed is $1,730.00
You earned 47 credits
)"));
}