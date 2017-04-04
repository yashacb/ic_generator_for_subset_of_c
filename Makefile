c:
	bison bison.y
	flex lexer.l
	gcc lex.yy.c -lfl -o test
	./test < ip.txt

t:
	bison bisonnnn.y
	flex lexer.l
	gcc lex.yy.c -lfl -o test
	./test < ip.txt