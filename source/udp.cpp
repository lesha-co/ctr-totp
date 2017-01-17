//
// Created by lichevsky on 15.01.17.
//




#include "udp.h"
#include "misc.h"

using namespace std;

UdpClient::UdpClient(std::string ip, u16 port) {
    slen=sizeof(si_other);
    prepareUDP(ip, port);
}



s8 UdpClient::prepareUDP(std::string ip, u16 port) {

    Result ret;

    // allocate buffer for SOC service
    SOC_buffer = (u32*)memalign(SOC_ALIGN, SOC_BUFFERSIZE);

    if(SOC_buffer == NULL) {
        printf("Failed to allocate aligned memory\n");
        return -1;
    }

    // Now initialise soc:u service
    if ((ret = socInit(SOC_buffer, SOC_BUFFERSIZE)) != 0) {
        printf("Failed to initialise soc:u service: 0x%08X\n", (unsigned int)ret);
        return -1;
    }
    // creating socket
    if ( (sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        printf("Failed to create socket");
        return -1;
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(port);

    if (inet_aton(ip.c_str() , &si_other.sin_addr) == 0) {
        printf("inet_aton() failed\n");
        return -1;
    }

    fcntl(sockfd, F_SETFL, O_NONBLOCK);
    return 0;
}

void UdpClient::send(std::vector<u8> vec) {
    if (vec.size() >= BUFLEN){
        printf("can't send messages longer than %d\n", BUFLEN);
    }
    ///run
    //printf("sending %d bytes:\n%s\n",vec.size(), misc::vector_u8_str(vec).c_str());
    memset(message,'\0', BUFLEN);
    for (u32 i = 0; i < vec.size(); ++i) {
        message[i] = vec[i];
    }
    //send the message

    if (sendto(sockfd, message, vec.size(), 0 , (struct sockaddr *) &si_other, slen)==-1) {
        printf("Failed to sendto()\n");
    }
}
std::vector<u8> UdpClient::recv() {
    memset(buf,'\0', BUFLEN);
	s32 recv_size;
	recv_size = recvfrom(sockfd,
		buf,
		BUFLEN,
		0,
		(struct sockaddr *) &si_other,
		&slen);
    if (recv_size == -1) {
        printf("Failed to recvfrom()\n");
		return vector<u8>();
    }
	vector<u8> response;
    for (s32 j = 0; j < recv_size; ++j) {
            response.push_back(buf[j]);
    }
    //printf("received:\n%s\n", misc::vector_u8_str(response).c_str());
    return response;
}


std::vector<u8> UdpClient::sendAndReceive(std::vector<u8> vec, u32 waitBeforeRecv=10000, s32 maxRetries=1) {

    std::vector<u8> result;
    do{
        send(vec);
        usleep(waitBeforeRecv);
        result = recv();
        maxRetries--;
    } while (result.size() == 0 && maxRetries > 0);
    return result;
}
UdpClient::~UdpClient() {
    exit();
}
void UdpClient::exit() {
    close(sockfd);

    // Exit services
    socExit();
    free(SOC_buffer);
}