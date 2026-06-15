#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include <string.h>

/* socket
* bind
* listen
* accept
* send/recv
*/

#define SERVER_PORT 8888

int main (int argc, char **argv)
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

    iSocketServer = socket(AF_INET, SOCK_STREAM, 0);
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
    if (iRet == -1)
    {
        printf("bind error!\n");
        return -1;
    }

    iRet = listen(iSocketServer, 10);
    if(iRet == -1)
    {
        printf("Listen error!\n");
        return -1;
    }

    while (1)
    {
        int iAddrLen_in = sizeof(struct sockaddr_in);
        iSocketClient = accept(iSocketServer, (struct sockaddr*)&tSocketClientAddr, &iAddrLen_in);
        if (iSocketClient != -1)
        {
            iClientNum++;
            printf("Get connect from %d: %s\n", iClientNum++, inet_ntoa(tSocketClientAddr.sin_addr));
            // fork 会负责制当给的代码创建子进程，子进程并不重头开始运行，而是同样
            // fork函数如果在子函数子进程返回0，父进程会返回子进程的PID执行fork
            if(!fork()) 
            {
                while (1)
                {
                    RecvLen = recv(iSocketClient, buffer, 999, 0);
                    if (RecvLen <= 0)
                    {
                        close(iSocketClient);
                        return -1;
                    }
                    else
                    {
                        buffer[RecvLen] = '\0';
                        printf("Recieved msg from Client %d: %s\n", iClientNum, buffer);
                    }
                }
            }
        }
    }
    close(iSocketServer);
    return 0; 
}