//
// Created by lichevsky on 12.01.17.
//


#include "base32.h"
using namespace std;
const string BASE32_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
const char BASE32_PADDING = '=';



vector<u8> base32::decode(std::string b32) {
    vector<u8> bytes;
    vector<u8> v_bits;

    if (b32.size() % 8) return {};
    for(u32 i = 0; i < b32.size(); ++i){
        u32 index;
        string::size_type loc = BASE32_ALPHABET.find( b32[i], 0 );
        if( loc != string::npos ) {
            index = loc;

        } else {
            return {};
        }
        vector<u8> piece = misc::leftpad(misc::int_to_bits(index), 5);
        /*printf(" |> %c (%3u)= ", b32[i], index);
        for(u8 bit : piece){
            printf(" %d ", bit);
        }
        printf("\n");*/
        v_bits.insert( v_bits.end(), piece.begin(), piece.end() );

        while (v_bits.size() >= 8){
            // get first 8 bits
            vector<u8>::const_iterator first = v_bits.begin();
            vector<u8>::const_iterator last = v_bits.begin() + 8;
            vector<u8> byte(first, last);
            /*printf("<|  %d (0x%x) (%c): ", bits_to_int(byte), bits_to_int(byte), bits_to_int(byte));
            for(u8 bit : byte){
                printf("%d", bit);
            }
            printf("\n");*/
            bytes.push_back (misc::bits_to_int(byte));
            // remove them from original vector
            vector<u8>(v_bits.begin()+8, v_bits.end()).swap(v_bits);
        }
    }

    return bytes;

}
