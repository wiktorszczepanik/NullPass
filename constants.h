#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <array>

const int WAIT_TIME = 10000;
namespace characters {
    const auto LOWERCASE = std::string("abcdefghijklmnopqrstuvwxyz");
    const auto UPPERCASE = std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    const auto DIGITS = std::string("0123456789");
    const auto SPECIAL = std::string("!@#$%^&*()-_=+[{]};:'\"|,<.>/?");
}
const std::array<std::string, 28> EMOJI = {
    "🕶️", "🐧", "🍎", "⚽", "🙂", "🎸", "👣", "🚩", "☢️", "🎁", "💣", "🤡", "🥤", "🌵",
    "🐬", "🌸", "🏹", "🔑", "🌶️", "🦊", "📷", "🎵", "🐼", "✉️", "🔔", "💎", "🫧", "🍕"
};
#endif // CONSTANTS_H
