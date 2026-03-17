#include "headerFiles.h"
int main(void) {
    int s;                          // Socket descriptor (reference)
    int len;                        // Length of string to be echoed
    char buffer[256];               // Data buffer
    struct sockaddr_in servAddr;    // Server (local) socket address
    struct sockaddr_in clntAddr;    // Client (remote) socket address
    int clntAddrLen;                // Length of client socket address

    // Build local (server) socket address
    memset(&servAddr,0,sizeof(servAddr));           // Allocate memory
    servAddr.sin_family = AF_INET;                  // Family field
    servAddr.sin_port = htons(SERVER_PORT);         // Default port number
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);   // Default IP address

    // Create socket
    if ((s = socket(PF_INET,SOCK_DGRAM,0)) < 0)
    {
        perror("Error: bind failed!");
        exit(1);
    }

    if (bind(s, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
    perror("bind failed");
    exit(1);
    }
    
    clntAddrLen = sizeof(clntAddr);

    for(;;)     // Run indefinitely
    {
        // Receive String
        len = recvfrom(s,buffer,sizeof(buffer),0,(struct sockaddr *)&clntAddr,&clntAddrLen);
        if (len < 0) {
            perror("recvfrom failed");
            continue;
        }
        // Send String
        sendto(s,buffer,len,0,(struct sockaddr *)&clntAddr,sizeof(clntAddr));
    }
}