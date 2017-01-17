//
// Created by lichevsky on 15.01.17.
//

#ifndef MAIN_EXEC_UDP_H
#define MAIN_EXEC_UDP_H


#include <3ds/types.h>
#include <vector>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include <3ds.h>
#include <arpa/inet.h>
#include <malloc.h>
#include <unistd.h>

#define BUFLEN 512	//Max length of buffer
#define SOC_ALIGN       0x1000
#define SOC_BUFFERSIZE  0x100000
class UdpClient {
public:
    UdpClient(std::string ip, u16 port);
    void exit();
    ~UdpClient();

    std::vector<u8> sendAndReceive(std::vector<u8>, u32, s32);
    std::vector<u8> recv();
    void send(std::vector<u8>);
private:
    s8 prepareUDP(std::string ip, u16 port);
    s32 sockfd;
    char message[BUFLEN];
    char buf[BUFLEN];
    sockaddr_in si_other;
    socklen_t slen;
    u32* SOC_buffer;
};


#endif //MAIN_EXEC_UDP_H
