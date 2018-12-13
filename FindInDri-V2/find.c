#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>

#define MAX_DEPTH 3

void FindInDir(char* folder, char* FindFileName, int depth)
{if(depth <= 0)
    return;
 else{
    printf("LookingFor:%s\n", FindFileName);
    DIR *dir;
    struct dirent *dp;
    char folder_tmp[258];
    dir = opendir(folder);
    //printf("depth:%d\n", depth);
    printf("Открытие папки %s \n",folder);

        while ((dp=readdir(dir)) != NULL){
            if (dp->d_type != 4){
                printf("NameNow:%s\n",dp->d_name);
                if(strcmp(dp->d_name, FindFileName) == 0)
                {
                    printf("\n!!!FOUND!!! It is here:%s\n\n", folder);
                    return;
                    break;
                }
            }
            else if((dp->d_type==4) && ((strcmp(dp->d_name,".") != 0) && (strcmp(dp->d_name,"..") != 0))){
                    //printf("here\n");
                    sprintf(folder_tmp,"%s/%s", folder,dp->d_name);
                    //printf("floderIs:%s\n", folder_tmp);
                    FindInDir(folder_tmp, FindFileName, (depth-1));
                    //break;
                }
        }
    closedir(dir);
 }
}

int main(int argc, char **argv)
{
    DIR *dir;
    struct dirent *dp;
    char dirname[256];
    char filename[256];
    int depth = MAX_DEPTH;
    if ( argc < 2 ) strcpy(dirname, ".");
            else strcpy(dirname, argv[1]);
    strcpy(filename, argv[2]);
    printf("Корневой каталог %s\n\n", dirname);
    FindInDir(dirname, filename, depth);
    printf("Search Ended\n");
    return 0;
}
