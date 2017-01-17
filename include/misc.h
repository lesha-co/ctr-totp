//
// Created by lichevsky on 14.01.17.
//

#ifndef MAIN_EXEC_MISC_H
#define MAIN_EXEC_MISC_H
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include "3ds.h"
class misc{
public:
    static std::string vector_u8_str(std::vector<u8> vec);
    static std::vector<u8> int_to_bits(u32 value);
    static u8 bits_to_int(std::vector<u8> vector);
    static std::vector<u8> int_to_bytes(u32 value);
    static u32 bytes_to_int(std::vector<u8> vector);
    static std::vector<u8> leftpad(std::vector<u8> v_source, u32 to_length);
};
#endif //MAIN_EXEC_MISC_H
