//
// Created by lichevsky on 12.01.17.
//

#ifndef MAIN_EXEC_BASE32_H
#define MAIN_EXEC_BASE32_H

#include <vector>
#include <string>
#include <math.h>
#include <3ds/types.h>

class base32 {
public:
    static std::vector<u8> decode(std::string b32);
    static u8 bits_to_int(std::vector<u8> vector);
    static std::vector<u8> int_to_bits(u32 value);
};


#endif //MAIN_EXEC_BASE32_H
