//
// Created by lichevsky on 15.01.17.
//
#include "../include/NTPClock.h"

using namespace std;

s32 NTPClock::getNetworkTime() {
    if (!client) {
        printf("Not initialized\n");
        return 0;
    }
    ntp_packet packet = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    //memset( &packet, 0, sizeof( ntp_packet ) );

    // Set the first byte's bits to 00,011,011 for li = 0, vn = 3, and mode = 3. The rest will be left set to zero.

    *((char *) &packet + 0) = 0x1b; // Represents 27 in base 10 or 00011011 in base 2.

    auto ptr = reinterpret_cast<char *>(&packet);
    vector <u8> message = vector < u8 > {ptr, ptr + sizeof(packet)};

    vector <u8> response = client->sendAndReceive(message, 1000000, 10);
    vector <u8> txTm_part(4);
    copy(response.begin() + 40, response.begin() + 44, txTm_part.begin());
    //printf("response (%u bytes): %s\n", response.size(), misc::vector_u8_str(response).c_str());
    //printf("txTm_part: %s\n", misc::vector_u8_str(txTm_part).c_str());

    u32 txTm_s = misc::bytes_to_int(txTm_part);

    // These two fields contain the time-stamp seconds as the packet left the NTP server.
    // The number of seconds correspond to the seconds passed since 1900.
    // ntohl() converts the bit/byte order from the network's to host's "endianness".
    printf("txTm_s: 0x%08lx\n", txTm_s);
    //txTm_s = ntohl(txTm_s); // Time-stamp seconds.
    printf("txTm_s(ntohl): 0x%08lx\n", txTm_s);
    // Extract the 32 bits that represent the time-stamp seconds (since NTP epoch) from when the packet left the server.
    // Subtract 70 years worth of seconds from the seconds since 1900.
    // This leaves the seconds since the UNIX epoch of 1970.
    // (1900)------------------(1970)**************************************(Time Packet Left the Server)
    unsigned long long NTP_TIMESTAMP_DELTA = 2208988800ull;
    time_t txTm = (time_t)(txTm_s - NTP_TIMESTAMP_DELTA);

    return txTm;
}

NTPClock::NTPClock(char *ntpServerIP) {
    client = new UdpClient(string(ntpServerIP), 123);
}

NTPClock::~NTPClock() {
    delete (client);
}

bool NTPClock::initialized() {
    return client != NULL;
}
