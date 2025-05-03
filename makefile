eon: eon_parser
	./eon_parser 

eon_parser: lex.yy.c y.tab.c
	gcc -o eon_parser lex.yy.c y.tab.c -ll

lex.yy.c: eon.l
	lex eon.l

y.tab.c: eon.y
	yacc -d eon.y

clean:
	rm -f eon eon_parser lex.yy.c y.tab.c y.tab.h