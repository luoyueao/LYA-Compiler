TEST_FILE=input/test.txt

compile: lex.l Syntax.y insertProcess.cpp flex.exe bison.exe input/test.txt
	flex.exe lex.l
	bison.exe Syntax.y -v -d
	g++ insertProcess.cpp -o insertProcess.exe
	insertProcess.exe
	g++ -o Syntax.tab.exe Syntax.tab.c lex.yy.c -w
	
clean:
	del /s /q Syntax.tab.h Syntax.tab.c Syntax.tab.exe lex.yy.c Syntax.output insertProcess.exe
	
run:
	Syntax.tab.exe < $(TEST_FILE)