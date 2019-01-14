/***************************************************************************************
File Name		: parser.h
Compiler		: MS Visual Studio 2015
Author			: Tanishq Bansal (040883753)
Course			: CST 8152 - Compilers, Lab Section: 014
Assignment		: 3
Date			: 6t December, 2018
Professor		: Sv. Ranev
Purpose			: This header file for parser
Function List	: -
****************************************************************************************/

#include "buffer.h"
#include "token.h"


#define NO_ATTR 0
#define ELSE 0
#define FALSE 1
#define IF 2
#define PLATYPUS 3
#define READ 4
#define REPEAT 5
#define THEN 6
#define TRUE 7
#define WHILE 8
#define WRITE 9

static Token lookahead;
int synerrno;
/*used for finding next token*/
extern Token malar_next_token();
/*str_LTBL : string literal table*/
extern Buffer* str_LTBL;
/*line: total number of lines in a program*/
extern int line;
/*keyword table*/
extern char *kw_table[];
/*as_table : state table*/
extern int as_table[];
/*accepting function callback table*/
extern int st_table[14][8];


















