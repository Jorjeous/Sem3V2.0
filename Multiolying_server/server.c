/* Программа 2 для иллюстрации работы с очередями сообщений */
//reciever
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define LAST_MESSAGE 255 /* Тип сообщения для прекращения работы */
#define AMOUNT 2
#define TIME 4
void Asem(int num, int a, int semid){
    struct sembuf mysembuf;

    mysembuf.sem_flg = 0;  /* Флаги операции */
    mysembuf.sem_num = num;/* Номер семафора */
    mysembuf.sem_op = a;   /* Операция над семафором */
    semop(semid, &mysembuf, 1);
}


int main(){
int msqid; /* IPC дескриптор для очереди сообщений */

char pathname[] = "server.c"; /* Имя файла, использующееся для генерации ключа.
Файл с таким именем должен существовать в текущей директории */

key_t key; /* IPC ключ */

int len, maxlen; /* Реальная длина и максимальная длина информативной части сообщения */

/* Ниже следует пользовательская структура для сообщения */

struct mymsgbuf{
    long mtype;
    int a;
    int b;
    int mypid;
} mybuf;


/* Генерируем IPC ключ из имени файла 09-1a.c в текущей директории
и номера экземпляра очереди сообщений 0  and generating key for semaphores*/

if((key = ftok(pathname,0)) < 0){
printf("Can\'t generate key\n");
exit(-1);
}
int semid;
key_t semkey;
semkey = ftok(pathname, 0);

if((semid = semget(semkey, 1, 0)) > 0)
{
    semctl(semid, IPC_RMID, 0);
}
semid = semget(semkey, 1, 0666 | IPC_CREAT);

Asem(0, AMOUNT, semid);

/* Пытаемся получить доступ по ключу к очереди сообщений, если она существует,
или создать ее, если она еще не существует, с правами доступа
read & write для всех пользователей */

if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
printf("Can\'t get msqid\n");
exit(-1);
}

while(1){

    /* В бесконечном цикле принимаем сообщения любого типа в порядке FIFO с максимальной длиной информативной части 81 символ до тех пор, пока не поступит сообщение с типом LAST_MESSAGE*/
    //printf("point1\n");
    maxlen = sizeof(mybuf) - sizeof(long);
    //printf("recived...wait");
    if(( len = msgrcv(msqid, &mybuf, maxlen, 1, 0) < 0)){
        printf("Can\'t receive message from queue\n");
        exit(-1);
    }
    printf("recived...ok");
    Asem(0, -1, semid);

    int pid = fork();
    if(pid == 0)
    {
        //printf("Working with new client, pid:%d\n", mybuf.mypid);
        int result;
        result = mybuf.a * mybuf.b;
        sleep(TIME);

        mybuf.mtype = mybuf.mypid;
        mybuf.a = result;

        len = sizeof(mybuf) - sizeof(long);



        if (msgsnd(msqid, &mybuf, len, 0) < 0){
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, NULL);
            exit(-1);
        }
        Asem(0, 1, semid);

    }


    printf("point1\n");
    /* Если принятое сообщение имеет тип LAST_MESSAGE, прекращаем работу и удаляем очередь сообщений из системы.
    В противном случае печатаем текст принятого сообщения. */

    printf("sending:%d\n", mybuf.a); //strange
    printf("id:%ld\n", mybuf.mtype); //strange

    /*if (msgsnd(msqid, &mybuf, len, 0) < 0){
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, NULL);
        exit(-1);
    }*/
}

return 0; /* Исключительно для отсутствия warning'ов при компиляции. */
}
