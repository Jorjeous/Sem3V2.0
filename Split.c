#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void FreeStringArr(char** stringArr, int countString)
{
    for(int i = 0; i < countString; i++)
        free(stringArr[i]);
    free(stringArr);
}

// Function gets pointer on string, delimiter and returns array of strings(answer)
// string - what we need to separate
// separator
// countString - amount of elements arrays of stings

char** Split(char* string, const char* separator, int* countString)
{
    const  int sizeStrArr = 15;
    char* token;
    char** stringArr;    // Mass of strings (answer)
    char* str;             // Just helpfull varible to create copies of strings
    int count;              // Current amount of strings array

    count = 0;

    stringArr = (char**)malloc(sizeStrArr * sizeof(char**)); // allocating memory farrays of strings
    str = (char*)malloc(strlen(string) + 1);      // allocating memory for copy of string
    strcpy(str,string);                         // creating a copy

    // Start
    token = strtok(str, separator);
    while (token != NULL) {
        // FIXIT: 1) магическая константа 20 
        // 2) Кажется, что после этого realloc нужно еще sizeeStrArr увеличить на 20 
        if (count >= sizeStrArr)
        {
            stringArr = realloc(stringArr, sizeof(char**)*(count+20));
        }
        stringArr[count] = (char*) malloc(strlen(token)+1); // Allocating memory for current token
        strcpy(stringArr[count], token);                   // Coping token array
        token = strtok(NULL, separator);
        count++;
    }

    free(str);

    *countString = count;
    return stringArr;
}



int main() {
    int countString;
    char** stringArr;
    char* getString;
  /*FILE *file;
    file = fopen("", "r");
    fgets(getString, 128, file); */

    getString = "When half way through the journey of our life I found that I was in a gloomy wood";

    stringArr = Split(getString, " ", &countString);

    for (int i = 0; i < countString; i++) {
        printf("%3d: %s\n", i, stringArr[i]);
    }

    FreeStringArr(stringArr, countString);


    return 0;
}
