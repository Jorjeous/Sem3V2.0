#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// frees what I have done)
void freeStringMas(char **StringMas, int countString)
{
    for(int i = 0; i < countString; i++)
        free(StringMas[i]);
    free(StringMas);
}

char ** StringMasMalloc(char **StringMas, int * SizeStrMas) {
    int SizeOfStrMas, count;
    char ** tempArrayString;


    count = SizeOfStrMas = *SizeStrMas;
    SizeOfStrMas  = SizeOfStrMas * 2 * sizeof(char**);
    tempArrayString = StringMas;
    StringMas = (char**)malloc(SizeOfStrMas);
    for(int i = 0; i < count; i++) 
    {
        StringMas[i] = tempArrayString[i];
    }
    free(tempArrayString);
    *SizeStrMas = SizeOfStrMas;
    return StringMas;
}
// Function gets pointer on string, delimiter and returns mass of strings(answer)
// string - what we need to separate
// separator
// countString - amount of elements in mass of stings
char** split(char *string, const char *separator, int *countString)
{
    char *token, *last;
    char ** StringMas;    // Mass of strings (answer)
    char * str;             // Just helpfull varible to create copies of strings
    int count;              // Current amount of strings in mas
    int SizeStrMas;

    count = 0;
    SizeStrMas = 15;
    StringMas = (char**)malloc(SizeStrMas * sizeof(char**)); // allocating memory for mass of strings
    str = (char*)malloc(strlen(string) + 1);      // allocating memory for copy of string
    strcpy(str,string);                         // creating a copy

    // Start
    token = strtok(str, separator);
    while (token != NULL) {
        if (count >= SizeStrMas)
        {
            StringMas = StringMasMalloc(StringMas,&SizeStrMas);
        }
        StringMas[count] = (char*) malloc(strlen(token)+1); // Allocating memory for current token
        strcpy(StringMas[count], token);                   // Coping token in mas
        token = strtok(NULL, separator);
        count++;
    }

    free(str);

    *countString = count;
    return StringMas;
}



int main() {
    int countString;
    char **StringMas;
    char *GetString;
    //scanf("%s", GetString);
    GetString = "When half way through the journey of our life I found that I was in a gloomy wood";

    StringMas = split(GetString, " ", &countString);

    for (int i = 0; i < countString; i++) {
        printf("%3d: %s\n", i, StringMas[i]);
    }

    freeStringMas(StringMas, countString);

    return 0;
}
