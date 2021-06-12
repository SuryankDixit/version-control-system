/* 
 *  The purpose of this file is to define and include the required
 *  libraries, function signatures, and defaults for the Git `.c`
 *  programs to function. This file <cache.h> is included in all
 *  the `.c` files in this same (root) directory
*/


#ifndef __CACHE__
#define __CACHE__

#include <iostream>      /* Standard C library defining input/output tools. */
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>   /* Standard C library defining `stat` tools. */
#include <fcntl.h>      /* Standard C library for working with files. */
#include <stddef.h>     /* Standard C library for type definitions. */
#include <stdlib.h>     /* Standard C library for library definitions. */
#include <stdarg.h>     /* Standard C library for variable argument lists. */
#include <errno.h>      /* Standard C library for system error numbers. */

using namespace std;

/* If desired, you can use an environment variable to set a custom path to the object store.*/
#define DB_ENVIRONMENT "SHA1_FILE_DIRECTORY"


/* The default path to the object store.*/
#define DEFAULT_DB_ENVIRONMENT ".dircache/objects"



#endif