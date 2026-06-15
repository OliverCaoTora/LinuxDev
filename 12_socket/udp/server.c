#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include <string.h>

/*socket
* bind(ip port)
* recvfrom/sendto
*/

#define SERVER_PORT 8888

int main(int argc, char **argv)
{
    int iSocketServer;
    struct sockaddr_in tSocketServerAddr;
    struct sockaddr_in tSocketClientAddr;
    int iSocketClient;

    int iRet;

    unsigned char buffer[1000];
    int RecvLen;
    
    int iClientNum = -1;

    signal(SIGCHLD,SIG_IGN);

    iSocketServer = socket(AF_INET, SOCK_DGRAM, 0);
    if (iSocketServer == -1)
    {
        printf("socket error!\n");
        return -1;
    }

    tSocketServerAddr.sin_family = AF_INET;
    tSocketServerAddr.sin_port = htons(SERVER_PORT);
    tSocketServerAddr.sin_addr.s_addr = INADDR_ANY; //本机上所有的IP
    memset(tSocketServerAddr.sin_zero, 0, 8);

    iRet = bind(iSocketServer, (struct sockaddr *)&tSocketServerAddr, sizeof(tSocketServerAddr));

    while (1)
    {
        int iAddrLen = sizeof(tSocketClientAddr);
        RecvLen = recvfrom(iSocketServer, buffer, 999, 0, (struct sockaddr *)&tSocketClientAddr, &iAddrLen);
        if (RecvLen > 0)
        {
            buffer[RecvLen] = '\0';
            printf("Get Msg from %s: %s\n", inet_ntoa(tSocketClientAddr.sin_addr), buffer);
        }
    }

    return 0;
}