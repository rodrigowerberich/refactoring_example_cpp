#pragma once

#include <string>
#include "plays.h"


namespace TheaterBilling
{

using Invoices = int;
std::string statement(const Plays& plays, const Invoices& invoices);

} // namespace TheaterBilling

