#include "crypto.h"

#include <stdexcept>
#include <string>
#include <openssl/evp.h>

auto crypto::PBKDF2_key(std::string passphrase, int iterations, int keyLength, unsigned char* key) -> void {
    auto salt = std::string("fixed salt for a reason :)");
    if (!PKCS5_PBKDF2_HMAC(passphrase.c_str(), passphrase.length(),
        reinterpret_cast<const unsigned char*>(salt.c_str()),
        salt.length(), iterations, EVP_sha512(), keyLength, key)) {
        throw std::runtime_error("Key creation failed.");
    }
}
