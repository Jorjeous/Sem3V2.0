#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>


#define BUFFERSIZE 50
#define NAMEDPIPE "/home/george/Desktop/projects/messege/myNamedPipe"

int main(int argc, char** argv)
{

    char buf[BUFFERSIZE];
    int fd, len;


    if(mkfifo(NAMEDPIPE, 0777))
    {
        perror("Ctreate");
        return 1;
    }
    printf("%s, is created", NAMEDPIPE);

    if( (fd = open(NAMEDPIPE, O_RDONLY)) <= 0)
    {
        perror("Open");
        return 1;
    }
    printf("%s, is opened", NAMEDPIPE);
    while(1){
        memset(buf, '\0', BUFFERSIZE);
        if ((len = read(fd, buf, BUFFERSIZE-1)) <= 0)
        {
            perror("Read");
            close(fd);
            remove(NAMEDPIPE);
            return 0;
        }
        printf("Incoming messege (%d): %s\n", len, buf);

    }
    return 0;
}
