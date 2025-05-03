#include <stdio.h>
#include "eon.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

char *names[] = {NULL,"int","float","char","string","bool"};

int main(void){
	int ntoken, vtoken;
	ntoken = yylex();
	while(ntoken){
		printf("%d\n", ntoken);
		ntoken = yylex();
	}
	return 0;
}