#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <map>
#include <tuple>

#include "statement.h"

using ::testing::StrEq;
using namespace TheaterBilling;

std::tuple<Plays, Invoice> createTestData1(){
    auto plays = Plays();
    plays["hamlet"] = Play("Hamlet", Play::Type::Tragedy);
    plays["as-like"] = Play("As You Like It", Play::Type::Comedy);
    plays["othello"] = Play("Othello", Play::Type::Tragedy);

    auto invoices = Invoice("BigCo", Performances{
        Performance("hamlet", 55),
        Performance("as-like", 35),
        Performance("othello", 40),    
    });

    return {plays, invoices};
}

std::tuple<Plays, Invoice> createTestData2(){
    auto plays = Plays();
    plays["death-salesman"] = Play("Death of a Salesman", Play::Type::Tragedy);
    plays["unc-van"] = Play("Uncle Vanya", Play::Type::Comedy);

    auto invoices = Invoice("Small Company", Performances{
        Performance("death-salesman", 10),
        Performance("unc-van", 70),
    });

    return {plays, invoices};
}

TEST(RefactoringTst, DataSet1) {
    auto [plays, invoice] = createTestData1();

    EXPECT_THAT(statement(invoice, plays), StrEq(
R"(Statement for BigCo
 Hamlet: $650.00 (55 seats)
 As You Like It: $580.00 (35 seats)
 Othello: $500.00 (40 seats)
Amount owed is $1,730.00
You earned 47 credits
)"));
}

TEST(RefactoringTst, DataSet2) {
    auto [plays, invoice] = createTestData2();

    EXPECT_THAT(statement(invoice, plays), StrEq(
R"(Statement for Small Company
 Death of a Salesman: $400.00 (10 seats)
 Uncle Vanya: $860.00 (70 seats)
Amount owed is $1,260.00
You earned 54 credits
)"));
}