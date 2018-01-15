#define _WIN32_WINNT 0x600

#include <iostream>
#include <windows.h>
#include <ws2tcpip.h>
#include <winsock2.h>
#include <vector>

using namespace std;

class TCPConnection{
public:
    SOCKET socket;

    int bytesSent = 0;
    int outGoingPacketLength = 0;

    int bytesReceived = 0;
    int incomingPacketLength = 0;
    vector<string> message;
};

bool startWinSock(){

    WSADATA wsaData;

    WORD ver = MAKEWORD(2,2);

    int wstart = WSAStartup(ver, &wsaData);

    if(wstart != 0){
        return false;
    }
    return true;
}

SOCKET CreateTCPSocket(){
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == INVALID_SOCKET){
        cerr << "Error creating socket! Quiting" << endl;
        return -1;
    }

    cout << "Socket creation successful" << endl;

    //bind address and port to the sock socket
    sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(1500);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if(bind(sock, (sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR){
        cerr << "Error binding socket! Quiting" << endl;
        return -1;
    }

    cout << "Address and port given to server" << endl;

    //listen for incoming connections
    if(listen(sock, SOMAXCONN) ==  SOCKET_ERROR){
        cerr << "Error listening for connections! Quiting" << endl;
        return -1;
    }

    cout << "Server is listening for connection" << endl;

    return sock;
}

fd_set CreateNewSet(){
    fd_set master;
    FD_ZERO(&master);
    return master;
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

int main(){

    SOCKET listening, connected;
    TCPConnection online, recvSock;
    int numBytes = 4096;
    char buffer[numBytes];
    string data;
    bool hasWelcomed = false;

    if(!startWinSock()){
        cerr << "Error starting winsock! Quiting" << endl;
        WSACleanup();
        return -1;
    }

    if((listening = CreateTCPSocket()) == -1){
        cout << "error oc";
    }

    //set as non blocking socket
    u_long iMode = 0;
    ioctlsocket(listening, FIONBIO, &iMode);

    fd_set master = CreateNewSet();

    timeval timeout;
    timeout.tv_usec = 500000;
    timeout.tv_sec = 0;

    FD_SET(listening, &master);
    int counter = 0;
    while(true){
        fd_set readfds = master;
        fd_set writefds = master;
        fd_set exceptfds = master;

        SOCKET connected;

        int sockCount = select(NULL, &readfds, &writefds, &exceptfds, &timeout);

        for(int i=0; i<sockCount; i++){
            online.socket = master.fd_array[i];
            ZeroMemory(buffer, numBytes);
            if(FD_ISSET(online.socket, &exceptfds)){
                PrintErrorCode(listening);
                cerr << "Ending server!" << endl;
                closesocket(listening);
                WSACleanup();
                return -1;
            }

            if(FD_ISSET(online.socket, &readfds)){
                if(online.socket == listening){
                    connected = accept(listening, nullptr, nullptr);
                    if(connected == INVALID_SOCKET){
                        cout << "Client could not be connected" << endl;
                    }else{
                        cout << "Client " << connected << " connected" << endl;
                        FD_SET(connected, &master);
                    }
                    continue;
                }
                else{
                    ZeroMemory(buffer, numBytes);
                    online.incomingPacketLength = numBytes;
                    int retval = recv(online.socket, (char*)&buffer+online.bytesReceived, online.incomingPacketLength - online.bytesReceived, 0);
                    if(retval <= 0){
                        cout << "Client " << online.socket << " has disconnected" << endl;
                        FD_CLR(online.socket, &master);
                        closesocket(online.socket);
                    }else if(retval > 0){
                        online.bytesReceived += retval;
                        if(FD_ISSET(online.socket, &writefds)){
                            for(int j=0; j<sockCount; j++){
                                recvSock.socket = writefds.fd_array[j];
                                if(recvSock.socket != online.socket && recvSock.socket != listening){
                                    recvSock.outGoingPacketLength = numBytes;
                                    retval = send(recvSock.socket, buffer, numBytes, 0);
                                    if(retval > 0){
                                        recvSock.bytesSent += retval;
                                        if(recvSock.bytesSent == recvSock.outGoingPacketLength){
                                            recvSock.message[counter] = buffer;
                                            recvSock.bytesSent = 0;
                                            cout << recvSock.message[counter];
                                        }
                                    }
                                }
                            }
                        }
                        online.bytesReceived = 0;
                    }
                    counter++;
                    continue;
                }
            }
        }
    }
    return 0;
}
