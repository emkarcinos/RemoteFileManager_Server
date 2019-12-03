#pragma once

/* CLIENT MESSAGES */

/* Asks for directory list */
#define C_DIR   "39235sendmedir"
/* Asks for a file number */
#define C_FILE  "62384filenumber"
/* Tells goodbye */
#define C_STOP  "34569goodbye"

/* SERVER MESSAGES */

/* Begin Directory list stream */
#define DIR_START   "48375dirstart"
/* End Directory list stream */
#define DIR_DONE    "35236dirdone"
/* Begin File stream */
#define FILE_START  "83568filestart"
/* End File stream */
#define FILE_DONE   "59837filedone"
/* File Error */
#define FILE_ERR    "14987fileerr"
/* Dir Error */
#define DIR_ERR     "39562direrr"
