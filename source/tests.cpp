//
// Created by lichevsky on 15.01.17.
//

#include "tests.h"
using namespace std;

void testSHA1(){
    vector<u8> v_message = {0x48, 0x65, 0x6c, 0x6c, 0x6f};
    vector<u8> hash = hmac::u8_sha1(v_message);
    string s_hash_correct = "0xf7ff9e8b7bb2e09b70935a5d785e0cc5d9d0abf0";
    string s_hash_real = misc::vector_u8_str(hash);

    printf("testSHA1: %s\n", s_hash_correct==s_hash_real?"OK":"FAIL");
}
void testHMAC_SHA1(){
    vector<u8> v_key = base32::decode("JBSWY3DPEHPK3PXP");
    vector<u8> v_message = {0x48, 0x65, 0x6c, 0x6c, 0x6f};
    vector<u8> bytes = hmac::encode(v_key, v_message);
    string s_real_hmac = misc::vector_u8_str(bytes);
    string s_valid_hmac = "0x94fe5c55cf27a5068d4fc9d6afefe2ce50848bb9";
    printf("testHMAC_SHA1: %s\n", s_real_hmac==s_valid_hmac?"OK":"FAIL");
}
void test_base32decode(){

    vector<u8> bytes = base32::decode("JBSWY3DPEHPK3PXP");
    string s_real_b32 = misc::vector_u8_str(bytes);
    string s_valid_b32 = "0x48656c6c6f21deadbeef";
    printf("test_base32decode: %s\n", s_real_b32==s_valid_b32?"OK":"FAIL");
}
void test_bytes_to_int(){
    vector<u8> bytes = {0x4a, 0x78, 0x7a, 0xf1};
    u32 i_valid = 1249409777;
    u32 i_real = misc::bytes_to_int(bytes);
    printf("test_bytes_to_int: %s\n", i_valid==i_real?"OK":"FAIL");
}
void tests::testAll(){
    testSHA1();
    test_base32decode();
    testHMAC_SHA1();
    test_bytes_to_int();
}

