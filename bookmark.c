#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Passing in length because I had issues doing it on this end
void printValue(char line[], long length) {
    char output[length];
    int i;
    for (i = 0; i < length; i++) {
        if (line[i] != ' ') {
            strncpy(output, line + i, length);
            printf("%s\n\n", output);
            break;
        }
    }
}

int main(void) {
    char ch;
    FILE *fp;

    char *value;
    //Default google bookmarks location for linux
    char *file_name = "/.config/google-chrome/Default/Bookmarks";
    //Get the home folder location
    value = getenv("HOME");

    //Open the file reader
    fp = fopen(strcat(value, file_name),"r"); // read mode

    //Null checking
    if( fp == NULL )
    {
        perror("Error while opening the file.n");
        exit(EXIT_FAILURE);
    }


    int index = 0;
    int lineAmount = 0;
    int lineLength = 0;
    int lineLengthCounter = 0;
    //Read the file to get amount of lines, and highest line length
    while( ( ch = fgetc(fp) ) != EOF ) {
        if (ch == '\n'){
            lineAmount++;
            if (lineLengthCounter > lineLength) {
                lineLength = lineLengthCounter;
            }
            lineLengthCounter = 0;
        } else
        lineLengthCounter++;
    }
    //Create array with lineAmount indices, and lineLength length inputs
    char lineArray[lineAmount][lineLength];
    //Create a line holder for reading the current line
    char line[lineLength];

    rewind(fp);
   
    while( ( ch = fgetc(fp) ) != EOF ) {
        //If end of line check current line
        if (ch == '\n'){
            //If it is a bookmark, print it
            if (strstr(line, "name"))
                printValue(line, sizeof(line));
            else if(strstr(line, "url") && !strstr(line, "type"))
                printValue(line, sizeof(line));

            //Saving in case I want to save the entire file to an array again later
            //strcpy(lineArray[index], line);
            
            //Clear the line
            memset(line,0,strlen(line));
            index++;
        } else
            //Add the character to the line
            line[strlen(line)] = ch;
    }
    
    fclose(fp);
    return 0;
}
