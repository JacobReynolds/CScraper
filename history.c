#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int main(void) {
    sqlite3 *db;
    sqlite3_stmt    *res;
    int error = 0;
    char *file_name = "/.config/google-chrome/Default/History";
    //Get the home folder location
    char *value = getenv("HOME");
    FILE *historyFile = fopen("history.txt", "w");

    //Chrome needs to be closed for this to work
    //This will close all Chrome instances
    //~20 lines below throws segfault when intensive calls are made, have to look into that.
    //system("pkill -f chrome");

    int rc = sqlite3_open(strcat(value, file_name), &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    
    const char *tail;

    //Throws segfault when adding other processes
    //GDB doesn't show much
    rc = sqlite3_prepare_v2(db, "SELECT * FROM urls", -1, &res, &tail); 

    while (sqlite3_step(res) == SQLITE_ROW) {
        //url
        //puts(sqlite3_column_text(res, 1));
        fprintf(historyFile, "url: %s\n", sqlite3_column_text(res, 1));
        fprintf(historyFile, "title: %s\n", sqlite3_column_text(res, 2));
        fprintf(historyFile, "view count: %s\n", sqlite3_column_text(res, 3));
        fprintf(historyFile, "%s", "\n");
        //title
        //puts(sqlite3_column_text(res, 2));
        //history
        //puts(sqlite3_column_text(res, 3));
        //Give a little extra spacing
        //puts("\n");
    }
    fclose(historyFile);
    sqlite3_finalize(res);
    sqlite3_close(db);

    return 0;
}