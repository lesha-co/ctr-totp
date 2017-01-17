//
// Created by lichevsky on 12.01.17.
//

#ifndef MAIN_EXEC_HMAC_H
#define MAIN_EXEC_HMAC_H

#include "sha1.hpp"
#include <vector>
#include <cstdio>
class hmac {
public:
    static std::vector<u8> encode(std::vector<u8> key, std::vector<u8> message);
    static std::vector<u8> u8_sha1(std::vector<u8> message);
};


#endif //MAIN_EXEC_HMAC_H
