#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 42001
#define MAXCHAR 1024

int main(){
    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr);

    char* hello = "Hello there!";
    sendto(server_fd, NULL, NULL, MSG_CONFIRM, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    char buffer[MAXCHAR];
    int serveraddr_len;
    int n = recvfrom(server_fd, (char*)buffer, MAXCHAR, MSG_WAITALL, (struct sockaddr*)&serveraddr, (socklen_t*)&serveraddr_len);
    buffer[n] = '\0';

    printf("Server: %s\n", buffer);

    return 0;
}