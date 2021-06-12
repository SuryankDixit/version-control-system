/*
 *  The purpose of this file is to be compiled into an executable
 *  called `init-db`. When `init-db` is run from the command line
 *  it will initialize a Git repository by creating the object
 *  store (a directory called `.dircache/objects` by default)
 *  which will store the content that users commit in order to
 *  track the history of the repository over time.
*/
 
#include "cache.h"

 
/* creating a directory and giving read, write and execute  permissions to the user.*/
#define MKDIR( path ) ( mkdir( path, 0700 ) )
 
 
int main(int argc , char **argv){
    
    /*
     * Attempt to create a directory called ".dircache" in the current directory. 
     * If it fails, "mkdir()"" will return -1 and the program will print an error message and exit.
     */
    if (MKDIR(".dircache") < 0) {
        perror("unable to create .dircache");
        exit(1);
    }
 
    /*
     * Allowing user to store object database in the desired path.
     * User can set environment variable SHA1_FILE_DIRECTORY to the desired path location. 
     */
    char *directory = (char*)getenv(DB_ENVIRONMENT);
 
    /*
     * This code block will only be executed if `sha1_dir` is NOT null, i.e., if the environment variable above was defined.
     * Stat: These functions return information about a file. 
     * stat() stats the file pointed to by path and fills in buf.
     * Know about stat structure: https://linux.die.net/man/2/stat
     */
    if (directory) {
        struct stat st;
        if (!(stat(directory, &st) < 0) && S_ISDIR(st.st_mode))
            return 1;
        fprintf(stderr, "DB_ENVIRONMENT set to bad directory %s: ", directory);
    }
 
    /*
     * If the SHA1_FILE_DIRECTORY is not defined
     * Set `sha1_dir` to the default value `.dircache/objects` as defined in 
     * "cache.h", then print a message to the screen conveying this.
     */
    directory = (char*)DEFAULT_DB_ENVIRONMENT;
    fprintf(stderr, "defaulting to Staging area\n");
 
    if(MKDIR(directory)<0){
        perror(directory);
        exit(1);
    }
 
    int len = strlen(directory);
    char* path = (char*)malloc(len+40);        // sha1 hash is 40 digit long in hexadecimal 
 
    /* Copy the `sha1_dir` to `path`. */
    memcpy(path, directory, len);
 
    for (int i = 0; i < 256; i++) {
        /*
         * Convert `i` to a two-digit hexadecimal number and append it to the 
         * path variable after the `.dircache/objects/` part. That way, each 
         * time through the loop we build up one of the following paths: 
         * .dircache/objects/00, .dircache/objects/ff
         */
        sprintf(path+len, "/%02x", i);
 
        /*
         * Attempt to create the current subdirectory. If it fails, `mkdir()` 
         * will return -1 and the program will print a message and exit.
         */
        if (MKDIR(path) < 0) {
            perror(path);
            exit(1);
        }
    }
    return 0;
}
