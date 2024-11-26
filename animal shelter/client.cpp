#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "AnimalClass.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int __cdecl main(int argc, char** argv)
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    //const char* sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    // Validate the parameters
    if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    int param = 1;
    while (param) {
        int key;
        std::cout << "Enter key" << std::endl;
        std::cout << "1 - Send cat, 2 - Search cat, 0 - Exit" << std::endl;
        std::cin >> key;
        char test[4];
        memcpy(test, reinterpret_cast<char*>(&key), sizeof(int));
        iResult = send(ConnectSocket, test, (int)strlen(test), 0);
        if (iResult == SOCKET_ERROR) {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        }
        else if (iResult == 0) {
            break;
        }
        printf("Bytes Sent: %ld\n", iResult);

        switch (key) {
        case 1: {
            Animals temp;
            std::cin >> temp;
            char data[sizeof(Animals)] = {};
            memcpy(data, reinterpret_cast<char*>(&temp), sizeof(Animals));
            iResult = send(ConnectSocket, data, sizeof(data), 0);
            if (iResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ConnectSocket);
                WSACleanup();
                return 1;
            }
            else if (iResult == 0) {
                break;
            }
            printf("Bytes Sent: %ld\n", iResult);

        }
        break;
        case 2: {
            //std::cout << "Enter parameters for search: Have breed? What gender? Is age less, than year or not?" << std::endl;
            struct filter {
                short int breed;
                short int sex;
                short int age;
            };
            filter flt;
            std::cout << "1 - Thoroughbred, 0 -Not purebred 2-not matter" << std::endl;
            std::cin >> flt.breed;
            std::cout << "0-Female, 1-Male, 2 - not matter" << std::endl;
            std::cin >> flt.sex;
            std::cout << "0- less then a year, 1-more then a year, 2 - not matter" << std::endl;
            if (not(flt.breed >= 0 and flt.breed <= 2) or not(flt.age >= 0 and flt.age <= 2) or not(flt.sex >= 0 and flt.sex <= 2)) {
                std::cout << "Error" << std::endl;
                iResult=send(ConnectSocket, reinterpret_cast<char*>(0), 0, 0);
                break;
            }
            char data[sizeof(filter)] = {};
            memcpy(data, reinterpret_cast<char*>(&flt), sizeof(filter));
            iResult = send(ConnectSocket, data, sizeof(data), 0);
            if (iResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ConnectSocket);
                WSACleanup();
                return 1;
            }
            else if (iResult == 0) {
                break;
            }
            printf("Bytes Sent: %ld\n", iResult);
        }
              break;
        }
        
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
            printf("Bytes received: %d\n", iResult);
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());
    }
    
    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // Receive until the peer closes the connection
    /*do {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
            printf("Bytes received: %d\n", iResult);
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while (iResult > 0);*/

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}