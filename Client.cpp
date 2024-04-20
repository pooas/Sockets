//
// Created by pooas on 4/17/2024.
//
#include <iostream>
#include "winsock2.h"
#include "ws2tcpip.h"



int main(){

    std::cout << "====*()** W11 Client Server *()**=======\n \n" << std::endl;
    std::cout << "====*()** Client *()**=======" << std::endl;
    std::cout << "==Client==*()** SETUP 1 -> Set up DLL *()**=======" << std::endl;

    SOCKET clientSocket;
    int port {55555};
    WSAData wsaData;
    int wsaerr;
    WORD mVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(mVersionRequested, &wsaData);
    if (wsaerr != 0)
    {
        std::cout << "The WinSock DLL not founded...!\n";
        return 0;
    }else{
        std::cout << "WinSock is OK ..." << '\n';
        std::cout << " The status : " << wsaData.szSystemStatus << '\n';

    }

    std::cout << "==Client==*()** SETUP 2 -> Set up Client Socket *()**=======" << std::endl;

    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET){
        std::cout << "The socket() has problem..." << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }else
    {
        std::cout << "The socket is Ok..." << std::endl;
    }

    std::cout << "==Client==*()** SETUP 3 -> Connect with Server Socket *()**=======" << std::endl;

    sockaddr_in clientServis;
    clientServis.sin_family = AF_INET;
    InetPton(AF_INET, "127.0.0.1", &clientServis);
    clientServis.sin_port = htons(port);

    if(connect(clientSocket, (SOCKADDR*)&clientServis, sizeof(clientServis)) == ERROR){
        std::cout << "Client connect- Failed to connect." << '\n';
        WSACleanup();
        return 0;
    }else{
        std::cout << "Client : The Connection() is OK..." << '\n';
        std::cout << "Client :  Client can starting sending and recieving data..." << '\n';
    }

    std::cout << "==Client==*()** SETUP 4 -> Start chat to the server  *()**=======" << std::endl;

    char buffer[200];

    std::cout << " Please enter the message to the server.. " << '\n';

    std::cin.getline(buffer, 200);

    int byteCount = send(clientSocket, buffer,200, 0);

    if (byteCount > 0)
        std::cout << "Message sent... : " << buffer << '\n';
    else
        WSACleanup();


    std::cout << "==Client==*()** SETUP 5 -> Close Socket  *()**=======" << std::endl;



    system("pause");
    WSACleanup();

    return 0;
}