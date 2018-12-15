

/* sender*/

/* Эта программа получает доступ к очереди сообщений,
отправляет в нее 5 текстовых сообщений с типом 1
и одно пустое сообщение с типом 255, которое будет служить
для программы 2 сигналом прекращения работы. */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define LAST_MESSAGE 255 /* Тип сообщения для прекращения работы программы 2 */

int main()
{
int msqid; /* IPC дескриптор для очереди сообщений */

char pathname[] = "server.c"; /* Имя файла, использующееся для генерации ключа.
Файл с таким именем должен существовать в текущей директории */

key_t key; /* IPC ключ */

int i,len; /* Cчетчик цикла и длина информативной части сообщения */

/* Ниже следует пользовательская структура для сообщения */

struct mymsgbuf{
    long mtype;
    int a;
    int b;
    int mypid;
} mybuf;

/* Генерируем IPC ключ из имени файла 09-1a.c в текущей директории
и номера экземпляра очереди сообщений 0. */

if((key = ftok(pathname,0)) < 0){
printf("Can\'t generate key\n");
exit(-1);
}

/* Пытаемся получить доступ по ключу к очереди сообщений, если она существует,
или создать ее, если она еще не существует, с правами доступа
read & write для всех пользователей */

if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
printf("Can\'t get msqid\n");
exit(-1);
}

/* Посылаем в цикле 5 сообщений с типом 1 в очередь сообщений, идентифицируемую msqid.*/




    /* Сначала заполняем структуру для нашего сообщения и определяем длину информативной части */
    int a = 0;
    int b = 0;
    scanf("%d %d", &a, &b);

    mybuf.mtype = 1;
    mybuf.a = a;
    mybuf.b = b;
    mybuf.mypid = getpid();
    len = sizeof(mybuf)-sizeof(long);


    /* Отсылаем сообщение. В случае ошибки сообщаем об этом и удаляем очередь сообщений из системы. */
    printf("sended...pre\n");
    if (msgsnd(msqid, &mybuf, len, 0) < 0){
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, NULL);
        exit(-1);
    }
    printf("sended...ok\n");



// recieving result


//printf("HI");
int maxlen = sizeof(mybuf)- sizeof(long);
printf("recieved...pre\n");
if(( len = msgrcv(msqid, &mybuf, maxlen, getpid(), 0) < 0)){
    printf("Can\'t receive message from queue\n");
    exit(-1);
}
printf("recieved...ok\n");
printf("id:%d\n", getpid());
printf("result:%d\n", mybuf.a);




return 0;
}
