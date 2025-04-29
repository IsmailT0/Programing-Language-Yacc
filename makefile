myprog: myprog.l myprog.y
    yacc -d myprog.y
    lex myprog.l
    gcc -o myprog lex.yy.c y.tab.c -ly -ll

clean:
    rm -f myprog lex.yy.c y.tab.c y.tab.h
