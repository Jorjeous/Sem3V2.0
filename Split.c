#include <stdio.h>
#include <stdlib.h>
#include <string.h>




// frees what I have done)
void FreeStringArr(char** StringArr, int CountString)
{
    for(int i = 0; i < CountString; i++)
        free(StringArr[i]);
    free(StringArr);
}

char** StringArrMalloc(char** StringArr, int* SizeStrArr) {
    int SizeOfStrArr, count;
    char** TempArrayString;

    // FIXIT: кажется, что вы пытались realloc реализовать {не совсем понял, что нужно Fixit, это просто подобие динамического выделения и вроде оно работает)}
    count = SizeOfStrArr = *SizeStrArr;
    SizeOfStrArr  = (*SizeStrArr) * 2 * sizeof(char**);
    TempArrayString = StringArr;
    StringArr = (char**)malloc(SizeOfStrArr);
    for(int i = 0; i < count; i++)
    {
        StringArr[i] = TempArrayString[i];
    }
    free(TempArrayString);
    *SizeStrArr = SizeOfStrArr;
    return StringArr;
}

// Function gets pointer on string, delimiter and returns array of strings(answer)
// string - what we need to separate
// separator
// CountString - amount of elements arrays of stings

char** split(char* string, const char* separator, int* CountString)
{
    const  int SizeStrArr = 15;
    char* token;
    char** StringArr;    // Mass of strings (answer)
    char* str;             // Just helpfull varible to create copies of strings
    int count;              // Current amount of strings array

    count = 0;
    
    StringArr = (char**)malloc(SizeStrArr * sizeof(char**)); // allocating memory farrays of strings
    str = (char*)malloc(strlen(string) + 1);      // allocating memory for copy of string
    strcpy(str,string);                         // creating a copy

    // Start
    token = strtok(str, separator);
    while (token != NULL) {
        if (count >= SizeStrArr)
        {
            StringArr = StringArrMalloc(StringArr, &SizeStrArr);
        }
        StringArr[count] = (char*) malloc(strlen(token)+1); // Allocating memory for current token
        strcpy(StringArr[count], token);                   // Coping token array
        token = strtok(NULL, separator);
        count++;
    }

    free(str);

    *CountString = count;
    return StringArr;
}



int main() {
    int CountString;
    char** StringArr;
    char* GetString;
    //scanf("%s", GetString);
    GetString = "When half way through the journey of our life I found that I was in a gloomy wood";

    StringArr = split(GetString, " ", &CountString);

    for (int i = 0; i < CountString; i++) {
        printf("%3d: %s\n", i, StringArr[i]);
    }

    FreeStringArr(StringArr, CountString);


    return 0;
}
