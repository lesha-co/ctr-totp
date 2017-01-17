//
// Created by lichevsky on 14.01.17.
//
#include "misc.h"
using namespace std;
string misc::vector_u8_str(vector<u8> vec){
    ostringstream o;
	o << "\n";
	for (size_t i = 0; i < 0x8; i++){
		o << ' ' << hex << setfill('0') << setw(2);
		o << (int)i;
	}
	for (size_t i = 0; i < vec.size(); i++){
		if (i % 0x8 == 0) {
			o << "\n";
		}
		o << ' ' << hex << setfill('0') << setw(2);
		o << (int)vec[i];

	}
    
    return  o.str();
}

vector<u8> misc::int_to_bits(u32 value){
    vector<u8> v_bits;
    while(value){
        v_bits.insert(v_bits.begin(), (u8)value % 2);
        value /= 2;
    }
    return v_bits;
}

u8 misc::bits_to_int(vector<u8> vec) {
    u8 byte = 0;
    for (u32 i = 0; i < vec.size(); ++i) {
        u32 power = vec.size() - 1 - i;
        byte += (1 << power) * vec[i];
    }
    return byte;
}

vector<u8> misc::leftpad(vector<u8> v_source, u32 to_length){

    if(v_source.size() > to_length){
        return v_source;
    } else {
        u32 difference = to_length - v_source.size();
        v_source.insert(v_source.begin(), difference, 0);
        return v_source;
    }
}

vector<u8> misc::int_to_bytes(u32 value){
    vector<u8> v_bits;
    while(value){
        v_bits.insert(v_bits.begin(), (u8)value % 256);
        value /= 256;
    }
    return v_bits;
}

u32 misc::bytes_to_int(vector<u8> vec) {
    u32 integer = 0;
    for (u32 i = 0; i < vec.size(); ++i) {
        u32 power = vec.size() - 1 - i;
        integer += pow(256, power) * vec[i] ;
    }
    return integer;
}