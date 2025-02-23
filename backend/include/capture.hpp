#ifndef CAPTURE_HPP
#define CAPTURE_HPP

#include <iostream>
#include <netinet/ip.h>   // Structure IP header
#include <netinet/tcp.h>  // Structure TCP header
#include <netinet/udp.h>  // Structure UDP header
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

class PacketSniffer {
public:
    PacketSniffer();
    ~PacketSniffer();
    void startCapture();
private:
    int sock_raw;
    void processPacket(unsigned char* buffer, int size);
};

#endif
