#pragma once

/* This file specifies the type of packets */

/* CLIENT MESSAGES */

/* Allows for data transfer */
#define C_ACK   'a'
/* Asks for directory list */
#define C_DIR   'd'
/* Asks for a file number */
#define C_FILE  'f'
/* Yes */
#define C_YES   'y'
/* No */
#define C_NO    'n'
/* Tells goodbye */
#define C_STOP  's'

/* SERVER MESSAGES */

/* A string */
#define T_STR   '1'
/* Directory list stream */
#define T_DIR   '2'
/* File stream */
#define T_FILE  '3'
/* A 64-bit integer */
#define T_LL    '4'
/* End of job */
#define DONEFOR '5'
/* Ask for user input */
#define USRIN   '6'
