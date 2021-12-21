#pragma once

#include <string>
#include "plays.h"
#include "invoice.h"


namespace TheaterBilling
{

std::string statement(const Plays& plays, const Invoice& invoices);

} // namespace TheaterBilling

