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

#define STR         '1'
/* Begin Directory list stream */
#define DIR_START   '2'
/* End Directory list stream */
#define DIR_DONE    '3'
/* Begin File stream */
#define FILE_START  '4'
/* End File stream */
#define FILE_DONE   '5'
/* File Error */
#define FILE_ERR    '6'
/* Dir Error */
#define DIR_ERR     '7'
