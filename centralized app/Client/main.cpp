#define _WIN32_WINNT 0x600

#include <iostream>
#include <windows.h>
#include <ws2tcpip.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

class TCPConnection{
public:
    SOCKET socket;

    int bytesSent = 0;
    int outGoingPacketLength = 0;

    int bytesReceived = 0;
    int incomingPacketLength = 0;
};

SOCKET ConnectToServer(){
    SOCKET connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(connection == INVALID_SOCKET){
        cerr << "Error creating socket! Quiting" << endl;
        WSACleanup();
        return -1;
    }
    cout << "Socket creation successful" << endl;
    //Fill socket structure
    sockaddr_in clientInfo;

    clientInfo.sin_family = AF_INET;
    clientInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientInfo.sin_port = htons(1500);

    u_long iMode = 0;
    ioctlsocket(connection, FIONBIO, &iMode);

    if(connect(connection, (sockaddr*)&clientInfo, sizeof(clientInfo)) == SOCKET_ERROR){
        cerr << "Could not connect to the server! Quiting" << endl;
        WSACleanup();
        return -1;
    }
    return connection;
}

void PrintErrorCode(SOCKET sock){
    int errorCode = 1;
    int sizeOfCode = sizeof(errorCode);

    if(getsockopt(sock, SOL_SOCKET, SO_ERROR, (char*)&errorCode, &sizeOfCode) == 0){
        cerr << "Winsock error occurred on socket " << sock << " with error code " << errorCode << endl;
    }else{
        cerr << "Winsock error occurred on " << sock << " and getsockopt() failed" << endl;
    }
}

fd_set CreateNewSet(){
    fd_set master;
    FD_ZERO(&master);
    return master;
}

bool startWinSock(){
    WSADATA wsaData;

    WORD ver = MAKEWORD(2,2);

    int wstart = WSAStartup(ver, &wsaData);

    if(wstart != 0){
        return false;
    }

    return true;
}

int main()
{
    if(!startWinSock()){
        cerr << "Error starting winsock! Quiting" << endl;
        return -1;
    }

    TCPConnection connection;
    connection.socket = ConnectToServer();
    if(connection.socket == -1){
        return connection.socket;
    }

    int numBytes = 4096;
    char buffer[numBytes];
    string data;

    fd_set master = CreateNewSet();

    timeval timeout;
    timeout.tv_usec = 500000;
    timeout.tv_sec = 0;

    FD_SET(connection.socket, &master);

    while(true){
        fd_set readfds = master;
        fd_set writefds = master;
        fd_set exceptfds = master;

        select(NULL, &readfds, &writefds, &exceptfds, &timeout);

        if(FD_ISSET(connection.socket, &exceptfds)){
            cerr << "Error with socket" << endl;
            closesocket(connection.socket);
            WSACleanup();
            return -1;
        }
        if(FD_ISSET(connection.socket, &readfds)){
            ZeroMemory(buffer, numBytes);
            connection.incomingPacketLength = numBytes;
            int retval = recv(connection.socket, (char*)&buffer + connection.bytesReceived, connection.incomingPacketLength - connection.bytesReceived, 0);
            if(retval <= 0){
                cout << "Server has closed, Shutting down" << endl;
                break;
            }else if(retval > 0){
                connection.bytesReceived += retval;
                if(connection.bytesReceived == connection.incomingPacketLength){
                    cout << buffer << endl;
                    connection.bytesReceived = 0;
                }
            }
        }
        if(FD_ISSET(connection.socket, &writefds)){
            cout << ">";
            getline(cin, data);
            ZeroMemory(buffer, numBytes);
            connection.outGoingPacketLength = numBytes;
            strcpy(buffer, data.c_str());
            int retval = send(connection.socket, (char*)&buffer + connection.bytesSent, connection.outGoingPacketLength - connection.bytesSent, 0);
            if(retval > 0){
                connection.bytesSent += retval;
                if(connection.bytesSent == connection.outGoingPacketLength){
                    connection.bytesSent = 0;
                }
            }
        }
    }
    //close the socket
    closesocket(connection.socket);
    WSACleanup();
    return 0;
}
