#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int sockfd;
    int n, len;
    char sendline[1000], recvline[1000];
    struct sockaddr_in servaddr, cliaddr;
    if(argc != 2){
        printf("Stop: \n");
        exit(1);
    }
    int port = atoi(argv[1]);
    if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
        exit(1);
    }
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(0);
    cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");


    if(bind(sockfd, (struct sockaddr *) &cliaddr, 
    sizeof(cliaddr)) < 0){
        perror(NULL);
        close(sockfd);
        exit(1);
    }


    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    scanf("%s",sendline);
    if(sendto(sockfd, sendline, strlen(sendline)+1, 0, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
    close(sockfd);
    exit(1);
    }
    printf("Recieving...");
    if((n = recvfrom(sockfd, recvline, 1000, 0, (struct sockaddr *) NULL, NULL)) < 0){

        close(sockfd);
        exit(1);
    }

    printf("\nresult:%f", atof(recvline));
    close(sockfd);
    return 0;
}



