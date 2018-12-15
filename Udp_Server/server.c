
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

    if(argc != 2){
      printf("Usage: %s <port>\n", argv[0]);
      exit(0);
    }
    int port = atoi(argv[1]);
    int sockfd;
    int clilen, n;
    char line1[1000];
    char line2[1000];
    struct sockaddr_in servaddr, cliaddr1, cliaddr2; /* Структуры для адресов сервера и клиента */


    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Создаем  сокет
    if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
        perror(NULL);
        exit(1);
    }

    if(bind(sockfd, (struct sockaddr *) &servaddr, 
    sizeof(servaddr)) < 0){
        close(sockfd);
        exit(1);
    }



        clilen = sizeof(cliaddr1);

        float a;
        float b;
        printf("Recieving");
        if((n = recvfrom(sockfd, line1, 999, 0, (struct sockaddr *) &cliaddr1, &clilen)) < 0){
            close(sockfd);
            exit(1);
        }

        printf("RCV(1)%s\n", line1);
        a = atof(line1);

        if((n = recvfrom(sockfd, line2, 999, 0, (struct sockaddr *) &cliaddr2, &clilen)) < 0){

            close(sockfd);
            exit(1);
        }
        printf("RCV(2):%s\n", line2);
        b = atof(line2);
        a = a+b;
        sprintf(line1,"%f", a);

        if(sendto(sockfd, line1, strlen(line1), 0, (struct sockaddr *) &cliaddr1, clilen) < 0){
            perror(NULL);
            close(sockfd);
            exit(1);
        }
        if(sendto(sockfd, line1, strlen(line1), 0, (struct sockaddr *) &cliaddr2, clilen) < 0){
            perror(NULL);
            close(sockfd);
            exit(1);
        }


    return 0;
}
