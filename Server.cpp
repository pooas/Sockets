#include <iostream>
#include "winsock2.h"
#include <ws2tcpip.h>


int main() {
    std::cout << "====*()** W11 Sockets *()**=======\n \n" << std::endl;
    std::cout << "====*()** SERVER *()**=======" << std::endl;
    std::cout << "====*()** SETUP 1 -> Set up DLL *()**=======" << std::endl;
    SOCKET serverSocket, acceptSocket;
    int port{55555};
    WSADATA wsaData;
    int wsaerr;
    WORD mVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(mVersionRequested, &wsaData);
    if (wsaerr != 0){
        std::cout << "The WinSock dll not found...!\n";
        return 0;
    }
    else {
        std::cout << " The WinSock found.\n";
        std::cout << "The status : " << wsaData.szSystemStatus << std::endl;
    }


    std::cout << "====*()** SETUP 2 -> Set up Server Sockets *()**=======" << std::endl;

    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET){
        std::cout << "Error at Socket() : " << WSAGetLastError() << std::endl;
        WSACleanup();
    }
    else
        std::cout << "Socket is OK.." << '\n';

    std::cout << "====*()** SETUP 3 -> Bind Socket *()**=======" << std::endl;


    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, ("127.0.0.1"), &service.sin_addr.s_addr);
    service.sin_port = htons(port);

    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service))==SOCKET_ERROR){
        std::cout << "bind() Failed : " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else
        std::cout << "bind() is OK..." << '\n';



    std::cout << "====*()** SETUP 4 ->  Initiate Listen *()**=======" << std::endl;

    if (listen(serverSocket,1) == SOCKET_ERROR)
        std::cout << "listen(): Error listening on socket" << WSAGetLastError() << std::endl;
    else
        std::cout << "Listen is OK. I'm waiting for connection ...." << '\n';



    std::cout << "====*()** SETUP 5 -> Accept Connection *()**=======" << std::endl;

    acceptSocket = accept(serverSocket, NULL, NULL);
    if(acceptSocket == INVALID_SOCKET){
        std::cout << "Accept Failed..." << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }


    std::cout << "==== *()** SETUP 6 -> Chat to client *()** =======" << std::endl;

    char buffer[200];


    int byteCount = recv(acceptSocket, buffer,200, 0);


    if (byteCount > 0)
        std::cout << "Message Received... : " << buffer << '\n';
    else
        WSACleanup();


    //else{
        // std::cout << "Accept Connections...." << '\n';
        // system("pause");
        // WSACleanup();
    //}

    return 0;
}
