#include "headerFiles.h"
int main (int argc, char* argv[]) 
{
    int s;                          // Socket descriptor
    int len;                        // Length of string to be echoed
    char* servName;                 // Server name
    int servPort;                   // Server port
    char* string;                   // String to be echoed
    char buffer[256+1];             // Data buffer
    struct sockaddr_in servAddr;    // Server socket address

    // Check and set program arguments
    if (argc != 4)
    {
        printf ("Error: three arguments are needed");
        exit(1);
    }

    servName = argv[1];
    servPort = atoi(argv[2]);
    string = argv[3];

    // Build server socket address
    memset(&servAddr,0,sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    inet_pton(AF_INET,servName,&servAddr.sin_addr);
    servAddr.sin_port = htons(servPort);

    // Create socket
    if ((s = socket(PF_INET,SOCK_DGRAM,0)) < 0)
    {
        perror("Error: Socket failed!");
        exit(1);
    }

    // Send echo string
    len = sendto(s,string,strlen(string),0,(struct sockaddr *)&servAddr,sizeof(servAddr));
    printf("Sending: %s\n", string);
    printf("Waiting for response...\n");
    //Receive echo string
    recvfrom(s,buffer,len,0,NULL,NULL);

    // Prin and verify echoed string
    buffer[len] = '\0';
    printf("Echo string received: ");
    fputs(buffer,stdout);
    
    // Close the socket
    close(s);

    // Stop the program
    exit(0);
}