//
// Created by lichevsky on 15.01.17.
//

#include "TOTP.h"
using namespace std;
const u32 TZOFFSET = 3*60*60;
u32 TOTP::getUnixEpochTime(){
    return (u32)time(0) - TZOFFSET;
}

u32 TOTP::getSeconds(){
    return getUnixEpochTime() - this->epoch;
}
u32 TOTP::getRemainingSeconds(){
    return this->interval - (this->getSeconds() % this->interval);
}
vector<u8> TOTP::getCounter(){
    u32 rounds = this->getSeconds() / this->interval;
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
TotpResult TOTP::get() {
    TotpResult tr;
    // 1. Calculate C as the number of times TI has elapsed after T0.
    vector<u8> counter = getCounter();
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
    tr.remaining_seconds= this->getRemainingSeconds();


    return tr;
}