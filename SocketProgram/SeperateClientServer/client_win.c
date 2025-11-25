#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <process.h>
// #include <unistd.h>
// #include <pthread.h>
// #include <arpa/inet.h>

#pragma comment(lib,"ws2_32.lib")

#define BUF 256
#define QUIT "quit"

int sockfd;

unsigned __stdcall sender(void* arg) {
    char msg[BUF];
    while (1) {
        fgets(msg, BUF, stdin);
        msg[strcspn(msg, "\n")] = 0;
        send(sockfd, msg, strlen(msg), 0);
        if (strcmp(msg, QUIT) == 0) exit(0);
    }
}

unsigned __stdcall receiver(void* arg) {
    char msg[BUF];
    while (1) {
        int n = recv(sockfd, msg, BUF-1, 0);
        if (n <= 0) { printf("Disconnected\n"); exit(0); }
        msg[n] = 0;
        printf("Server: %s\n", msg);
        if (strcmp(msg, QUIT) == 0) exit(0);
    }
}

int main(int argc, char *argv[]) {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2),&wsa);

    if (argc != 3) {
        printf("Usage: %s <server-ip> <port>\n", argv[0]);
        return 1;
    }

    char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET , ip, &addr.sin_addr);

    connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    printf("Connected to server!\n");

    uintptr_t t1= _beginthreadex(NULL,0,sender,NULL,0,NULL);
    uintptr_t t2= _beginthreadex(NULL,0,receiver,NULL,0,NULL);

    WaitForSingleObject((HANDLE)t1,INFINITE);
    WaitForSingleObject((HANDLE)t2,INFINITE);

    // pthread_t t1, t2;
    // pthread_create(&t1, NULL, sender, NULL);
    // pthread_create(&t2, NULL, receiver, NULL);

    // pthread_join(t1, NULL);
    // pthread_join(t2, NULL);
    closesocket(sockfd);
    WSACleanup();
}
