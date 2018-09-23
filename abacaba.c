#include <stdio.h>
//#include <malloc.h>
//#include <mem.h>
#include <stdlib.h>
#include <string.h>

// все закомментированные и лишние пустые строки нужно удалять

void GenStr(int n, char *string){
    char str[1];
    int i;


    if(n < 1)
    {
        return;
    }

    string[0] = 'a';
    //printf("%s", string);

    for(i = 1; i < n; i++){
        str[0] = (char) ('a' + i);
        strcat(string, str);
        strncpy(string + (1 << i), string, (1<< i) - 1);
        //printf("||%s||\n", string);
    }
}

int main() {
    int n;
    char *a;
    scanf("%d", &n);
    a = calloc((1 << n), sizeof(char));

    GenStr(n, a);

    printf("%s", a);

    return 0;
}
