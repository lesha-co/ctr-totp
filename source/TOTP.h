//
// Created by lichevsky on 15.01.17.
//

#ifndef MAIN_EXEC_TOTP_H
#define MAIN_EXEC_TOTP_H

#include "base32.h"
#include "hmac.h"
#include "misc.h"
#include "3ds.h"
#include <vector>
#include <string>
#include <ctime>
struct TotpResult{
    std::string totp;
    u8 remaining_seconds;
    std::vector<u8> hmac;
    std::vector<u8> four_bytes;
    u8 offset;
    u32 integer;
};

class TOTP {
    std::vector<u8> key;
    u32 epoch;
    u32 interval;
    u8 token_length;
public:
    TOTP(std::string secret_base32, u32 epoch, u32 interval, u8 token_length);
    TotpResult get(u32 unixEpochTime);
private:
    u32 getRemainingSeconds(u32 unixEpochTime);
    u32 getSeconds(u32 unixEpochTime);
    std::vector<u8> getCounter(u32 unixEpochTime);
    static u32 getUnixEpochTime();
};

#endif //MAIN_EXEC_TOTP_H
