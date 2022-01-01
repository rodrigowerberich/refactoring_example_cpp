#pragma once

#include <string>
#include "plays.h"
#include "invoice.h"


namespace TheaterBilling
{

std::string statement(const Invoice& invoices, const Plays& plays);

} // namespace TheaterBilling

