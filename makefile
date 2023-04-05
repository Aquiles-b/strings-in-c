saida: strings.c
	gcc strings.c -o saida -g -Wall -std=c99

run: saida
	./saida

clean: 
	rm saida 
