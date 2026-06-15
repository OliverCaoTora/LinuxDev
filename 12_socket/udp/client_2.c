#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

#include <string.h>

/* socket
* connect
* sendto/recv
*/

#define SERVER_PORT 8888

int main(int argc, char **argv)
{
    int iSocketClient;
    int iRet;
    struct sockaddr_in tSocketServerAddr;

    unsigned char buffer[1000];

    int iSendLen;

    if(argc != 2)
    {
        printf("Usage: %s <server_ip_addr>\n", argv[0]);
    }

    iSocketClient = socket(AF_INET, SOCK_DGRAM, 0);
    
    tSocketServerAddr.sin_family = AF_INET;
    tSocketServerAddr.sin_port = htons(SERVER_PORT);
    if(inet_aton(argv[1], &tSocketServerAddr.sin_addr) == 0)
    {
        printf("invalid serer_ip\n");
        return -1;
    }
    memset(tSocketServerAddr.sin_zero, 0, 8);

#if 0
    iRet = connect(iSocketClient, (struct sockaddr *)&tSocketServerAddr, sizeof(tSocketServerAddr));
    if(iRet < 0)
    {
        printf("Invalid connection.\n");
        return -1;
    }
#endif

    while (1)
    {
        if (fgets(buffer, 999, stdin)){
#if 0
            iSendLen = send(iSocketClient, buffer, strlen(buffer), 0);
#else
            int iAddrLen = sizeof(tSocketServerAddr);
            iSendLen = sendto(iSocketClient, buffer, strlen(buffer), 0, (const struct sockaddr *)&tSocketServerAddr, iAddrLen);
#endif

            if (iSendLen <= 0)
            {
                close(iSocketClient);
                return -1;
            }
        }
    }
    close(iSocketClient);

    return 0;
}