#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include<string>
#include<valarray>
#include<vector>
#include"bd.h"
#include"AnimalClass.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

typedef unsigned char byte;

using namespace std;


int __cdecl main(void)
{
    BD dataBase = {};
    dataBase.read();
    dataBase.print();
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    // Receive until the peer shuts down the connection
    do {

        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

            char rec[4] = {};
            for (int i = 0; i < iResult; i++) {
                rec[i] = recvbuf[i];
            }

            int testint = {};
            memcpy(reinterpret_cast<char*>(&testint), rec, sizeof(int));
            printf("%d\n", testint);
            switch (testint)
            {
            case 1:
            {
                iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
                printf("Bytes received: %d\n", iResult);
                Animals temp;
                char rec[sizeof(Animals)] = {};
                for (int i = 0; i < sizeof(Animals); i++) {
                    rec[i] = recvbuf[i];
                }
                memcpy(reinterpret_cast<char*>(&temp), rec, sizeof(Animals));
                cout << temp << endl;
                dataBase.add(temp);
            }
            break;
            case 2:
            {
                iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
                struct filter {
                    short int breed;
                    short int sex;
                    short int age;
                };
                char rec[sizeof(filter)] = {};
                filter flt;
                for (int i = 0; i < iResult; i++) {
                    rec[i] = recvbuf[i];
                }
                memcpy(reinterpret_cast<char*>(&flt), rec, sizeof(filter));
                vector<Animals>KotikiFil = {};
                int count = dataBase.search(flt.breed, flt.sex, flt.age, &KotikiFil);
                if (count == 0) {
                    char empty[4] = {};
                    memcpy(empty, reinterpret_cast<char*>(&count), sizeof(int));
                    iResult = send(ClientSocket, empty, sizeof(empty), 0);
                    break;
                }
                unsigned long int numberInt = KotikiFil.size();
                //cout << "Filtr getted" << endl;

                char number[8] = {};

                memcpy(number, reinterpret_cast<char*>(&numberInt), sizeof(number));

                iResult = send(ClientSocket, number, sizeof(number), 0);
                iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
                char* data{ new char(sizeof(Animals) * numberInt) };
                memcpy(data, reinterpret_cast<char*>(&(KotikiFil[0])), sizeof(Animals) * numberInt);
                vector<Animals>test;
                test.resize(numberInt);
                memcpy(reinterpret_cast<char*>(&(test[0])), data, sizeof(Animals) * numberInt);
                for (int i = 0; i < numberInt; i++) {
                    cout << test[i] << endl;
                }
                iResult = send(ClientSocket, data, sizeof(Animals) * numberInt, 0);

            }
            break;
            case 3: {
                char data[8] = {};
                unsigned long int id = {};
                iResult = recv(ClientSocket, data, sizeof(data), 0);
                memcpy(reinterpret_cast<char*>(&id), data, sizeof(id));
                if (id > dataBase.size()) {
                    char data[4] = {};
                    int zero = 0;
                    memcpy(data, reinterpret_cast<char*>(&zero), sizeof(int));
                    iResult = send(ClientSocket, 0, 0, 0);
                    break;
                }
                Animals temp = dataBase.takeCat(id);
                char dataKot[sizeof(Animals)] = {};
                memcpy(dataKot, reinterpret_cast<char*>(&temp), sizeof(Animals));

                iResult = send(ClientSocket, dataKot, sizeof(Animals), 0);
            }
                  break;
            default:
                break;
            }
            // Echo the buffer back to the sender
            /*iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %d\n", iSendResult);*/
        }
        else if (iResult == 0) {
            printf("Connection closing...\n");
            break;
        }
        else {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }
        char* sendbuf = recvbuf;
        iResult = send(ClientSocket, sendbuf, sizeof(sendbuf), 0);

    } while (iResult > 0);

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}