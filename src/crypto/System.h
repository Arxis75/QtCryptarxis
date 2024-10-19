#include <givaro/modular-integer.h>

#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/modes.h>
#include <openssl/kdf.h>
#include <openssl/core_names.h>
#include <openssl/params.h>
#include <openssl/err.h>

#include <ethash/keccak.hpp>

using ethash::hash256;

using Givaro::Modular;

typedef Modular<Givaro::Integer> ZP;
typedef ZP::Element Element;