#include "support.h"
#include "constants.h"

#include <string>
#include <stdexcept>

auto support::create_charset(bool lower, bool upper, bool digits, bool special) -> std::string {
    auto char_set = std::string();
    if (lower) char_set += characters::LOWERCASE;
    if (upper) char_set += characters::UPPERCASE;
    if (digits) char_set += characters::DIGITS;
    if (special) char_set += characters::SPECIAL;
    if (char_set.empty())
        throw std::runtime_error("At least one set of the characters must be selected.");
    return char_set;
}
