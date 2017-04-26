c:
	bison bison.y
	flex lexer.l
	gcc lex.yy.c -lfl -o test
	./test < ip.txt

t:
	bison aio.y
	flex lexer.l
	gcc lex.yy.c -lfl -o test
	./test < ip.txt