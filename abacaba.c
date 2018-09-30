#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GenStr(int n, char *string){
    char str[1];
    int i;
    if(n < 1)
    {
        return;
    }
    string[0] = 'a';
    
    for(i = 1; i < n; i++){
        str[0] = (char)('a' + i);
        strcat(string, str);
        strncpy(string + (1 << i), string, (1 << i) - 1);
    }
}

int main() {
    int n;
    char *a;
    scanf("%d", &n);
    a = calloc(1 << n, sizeof(char));

    GenStr(n, a);

    printf("%s", a);

    return 0;
}
