#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#define PORT 4444
#pragma comment(lib,"ws2_32.lib")

int main () {
	
	WSADATA wsa;
	SOCKET srvSocket , new_socket;
	struct sockaddr_in server , client;
	ssize_t size;
     
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
    
    printf("Initialised.\n");
    
    srvSocket = socket(AF_INET,SOCK_STREAM,0);
	
	if (srvSocket == INVALID_SOCKET) {
		printf("Could not create socket : %d" , WSAGetLastError());
	} 
	
	printf("Socket created.\n");
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( PORT );
	

    if( bind(srvSocket ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
    }
      
    puts("Bind done");
    
    listen(srvSocket,3);
    
    int c = sizeof(struct sockaddr_in);
    new_socket = accept(srvSocket , (struct sockaddr * )&client,&c);
    if (new_socket == INVALID_SOCKET) {
    	printf("accept failed with error code : %d" , WSAGetLastError());
	}
    
    puts("Connection accepted");
    int count = 0;
    while (1) {
	
    char message[327680];
    size = recv (new_socket , message, 327680,0);
    
    if (size == -1) {
    	if (count == 0) {
		
    	fprintf(stderr, "recv: %s (%d)\n", strerror(errno), errno);}
    	else {
    		printf("\n****************CLIENT DISCONNECTED****************");
    		break;
		}
    	
    	
	}
	
    else {
    	
    	count = count + 1;
    	message[size] = '\0';
    	printf(message); }
}
    getchar();
    
    closesocket(srvSocket);
    WSACleanup();
      
    return 0;
    
	
	
    
} 
