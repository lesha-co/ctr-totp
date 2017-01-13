//
// Created by lichevsky on 12.01.17.
//



#include "hmac.h"
using namespace std;
const u8 BLOCK_SIZE = 64;
const u8 O_KEY_PAD_BASE = 0x5c;
const u8 I_KEY_PAD_BASE = 0x36;

void print_u8(vector<u8> bytes){
    for (u8 byte : bytes) {
        printf("%x", byte);
    }
    printf("\n");
}

vector<u8> xor_vectors(vector<u8> a, vector<u8> b){
    vector<u8> result;
    for (int i = 0; i < a.size(); ++i) {
        result.push_back(a[i] ^ b[i]);
    }
    return result;
}

vector<u8> concat_vectors(vector<u8> A, vector<u8> B){
    vector<u8> result;
    result.reserve( A.size() + B.size() ); // preallocate memory
    result.insert( result.end(), A.begin(), A.end() );
    result.insert( result.end(), B.begin(), B.end() );
}



vector<u8> u8_sha1(vector<u8> message){
    SHA1 checksum;
    checksum.update(message);
    vector<u8> result = checksum.final_bytes();
    printf("hash: \n");
    print_u8(message);
    printf("->\n");
    print_u8(result);
    return result;
}

using namespace std;
vector<u8> hmac::encode(vector<u8> key, vector<u8> message){
    vector<u8> new_key  = vector<u8>(key.begin(), key.end());
    if(new_key.size() > BLOCK_SIZE){
        new_key = u8_sha1(new_key);
    }
    if(new_key.size() < BLOCK_SIZE){
        u32 difference = BLOCK_SIZE - new_key.size();
        new_key.insert(new_key.begin(), difference, 0);
    }

    vector<u8> o_key_pad;
    o_key_pad.insert(o_key_pad.begin(), BLOCK_SIZE, O_KEY_PAD_BASE);
    o_key_pad = xor_vectors(o_key_pad, key);

    vector<u8> i_key_pad;
    i_key_pad.insert(i_key_pad.begin(), BLOCK_SIZE, I_KEY_PAD_BASE);
    i_key_pad = xor_vectors(i_key_pad, key);

    return u8_sha1(
        concat_vectors(
            o_key_pad,
            u8_sha1(concat_vectors(
                i_key_pad, message
            ))
        )
    );


}