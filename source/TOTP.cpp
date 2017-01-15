//
// Created by lichevsky on 15.01.17.
//

#include "TOTP.h"
using namespace std;

u32 TOTP::getSeconds(u32 unixEpochTime){
    return unixEpochTime - this->epoch;
}

u32 TOTP::getRemainingSeconds(u32 unixEpochTime){
    return this->interval - (this->getSeconds(unixEpochTime) % this->interval);
}

vector<u8> TOTP::getCounter(u32 unixEpochTime){
    u32 rounds = this->getSeconds(unixEpochTime) / this->interval;
    vector<u8> vec = misc::int_to_bytes(rounds);
    vec = misc::leftpad(vec, 8);
    return vec;
}

TOTP::TOTP(std::string secret_base32, u32 epoch, u32 interval, u8 token_length){
    this->key = base32::decode(secret_base32);
    this->epoch = epoch;
    this->interval = interval;
    this->token_length = token_length;
}

TotpResult TOTP::get(u32 unixEpochTime) {
    TotpResult tr;
    // 1. Calculate C as the number of times TI has elapsed after T0.
    vector<u8> counter = getCounter(unixEpochTime);
    // 2. Compute the HMAC hash H with C as the message and K as the key (the HMAC algorithm is defined in the
    //    previous section, but also most cryptographical libraries support it). K should be passed as it is, C should
    //    be passed as a raw 64-bit unsigned integer.
    vector<u8> HMAC = hmac::encode(this->key, counter);
    // 3. Take the least 4 significant bits of H and use it as an offset, O.
    u8 offset = HMAC.back() & 0xf;
    // 4. Take 4 bytes from H starting at O bytes MSB, discard the most significant bit and store the rest as an
    //    (unsigned) 32-bit integer, I.
    vector<u8> four_bytes(HMAC.begin() + offset, HMAC.begin() + offset + 4);
    u32 integer = misc::bytes_to_int(four_bytes) & 0x7fffffff;

    // 5. The token is the lowest N digits of I in base 10. If the result has fewer digits than N, pad it with zeroes
    //    from the left.

    u32 otp = integer % (u32)(pow(10, this->token_length));

    ostringstream s;
    s << setw(this->token_length) << setfill('0') << otp;
    tr.totp = s.str();
    tr.hmac = HMAC;
    tr.offset = offset;
    tr.integer = integer;
    tr.four_bytes = four_bytes;
    tr.remaining_seconds= this->getRemainingSeconds(unixEpochTime);
    return tr;
}