/*
 * author: alikaanbaci
 * created date: Sunday August 4th 2019
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CHUNK 100

char* read_file(char* file_name){

    FILE* file;
    char ch;
    char* buf = NULL;
    int count = 100;
    
    file = fopen(file_name, "r");
    ch = fgetc(file);

    while (ch != EOF){
        if(count % CHUNK == 0){
            char* new = (char*) realloc(buf, count * sizeof(char*));
            buf = new;
        }
        buf[count-CHUNK] = ch;
        ch = fgetc(file);
        count++;
    }

    fclose(file);
    
    return buf;
}
