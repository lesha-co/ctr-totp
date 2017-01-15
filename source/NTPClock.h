//
// Created by lichevsky on 15.01.17.
//

#ifndef MAIN_EXEC_CLOCK_H
#define MAIN_EXEC_CLOCK_H

#include "udp.h"
#include "misc.h"
#include <netdb.h>
#include "3ds.h"
typedef struct
{

    unsigned li   : 2;       // Only two bits. Leap indicator.
    unsigned vn   : 3;       // Only three bits. Version number of the protocol.
    unsigned mode : 3;       // Only three bits. Mode. Client will pick mode 3 for client.

    uint8_t stratum;         // Eight bits. Stratum level of the local NTPClock.
    uint8_t poll;            // Eight bits. Maximum interval between successive messages.
    uint8_t precision;       // Eight bits. Precision of the local NTPClock.

    uint32_t rootDelay;      // 32 bits. Total round trip delay time.
    uint32_t rootDispersion; // 32 bits. Max error aloud from primary NTPClock source.
    uint32_t refId;          // 32 bits. Reference NTPClock identifier.

    uint32_t refTm_s;        // 32 bits. Reference time-stamp seconds.
    uint32_t refTm_f;        // 32 bits. Reference time-stamp fraction of a second.

    uint32_t origTm_s;       // 32 bits. Originate time-stamp seconds.
    uint32_t origTm_f;       // 32 bits. Originate time-stamp fraction of a second.

    uint32_t rxTm_s;         // 32 bits. Received time-stamp seconds.
    uint32_t rxTm_f;         // 32 bits. Received time-stamp fraction of a second.

    uint32_t txTm_s;         // 32 bits and the most important field the client cares about. Transmit time-stamp seconds.
    uint32_t txTm_f;         // 32 bits. Transmit time-stamp fraction of a second.

} ntp_packet;              // Total: 384 bits or 48 bytes.
class NTPClock {
public:
    NTPClock(char* ntpServerDomain);
    ~NTPClock();
    s32 getNetworkTime();
    bool initialized();
private:
    std::string ntpServerIP;
    UdpClient* client;
};


#endif //MAIN_EXEC_CLOCK_H
