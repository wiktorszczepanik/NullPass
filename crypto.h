#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

class crypto {
public:
    auto static PBKDF2_key(std::string, int, int, unsigned char*) -> void;
};

#endif // CRYPTO_H
