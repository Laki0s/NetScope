#include "capture.hpp"
#include <netinet/if_ether.h>

PacketSniffer::PacketSniffer() {
    sock_raw = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock_raw < 0) {
        perror("Socket Error");
        exit(EXIT_FAILURE);
    }
    std::cout << "Sniffer démarré..." << std::endl;
}

PacketSniffer::~PacketSniffer() {
    close(sock_raw);
}

void PacketSniffer::startCapture() {
    unsigned char buffer[65536];
    struct sockaddr saddr;
    socklen_t saddr_size = sizeof(saddr);

    while (true) {
        int data_size = recvfrom(sock_raw, buffer, sizeof(buffer), 0, &saddr, &saddr_size);
        if (data_size < 0) {
            perror("Recvfrom Error");
            exit(EXIT_FAILURE);
        }
        processPacket(buffer, data_size);
    }
}

void PacketSniffer::processPacket(unsigned char* buffer, int size) {
    struct iphdr* ip_header = (struct iphdr*)(buffer + 14);
    struct sockaddr_in source, dest;
    source.sin_addr.s_addr = ip_header->saddr;
    dest.sin_addr.s_addr = ip_header->daddr;

    std::cout << "IP Source: " << inet_ntoa(source.sin_addr)
              << " -> Destination: " << inet_ntoa(dest.sin_addr)
              << std::endl;
}
