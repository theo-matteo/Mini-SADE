all:
	gcc -g -Wall -o main *.c 

script:
	gcc main.c tFila.c tReceita.c tDocumento.c -o main

caso1:
	./main Casos/1 < Casos/1/entrada.txt

caso2:
	./main Casos/2 < Casos/2/entrada.txt

caso3:
	./main Casos/3 < Casos/3/entrada.txt

caso4:
	./main Casos/4 < Casos/4/entrada.txt

caso5:
	./main Casos/5 < Casos/5/entrada.txt

todoscasos:	caso1 caso2	caso3 caso4 caso5

cleanbancoetapa1:
	rm -r *.bin
	rm -r Casos/07/*.bin

cleanbancoetapa2:	
	rm Casos/01/consultas.bin Casos/01/lesoes.bin Casos/01/medicos.bin Casos/01/pacientes.bin Casos/01/secretarios.bin
	rm -r Casos/03/*.bin

cleancasosetapa1: 
	rm -r Casos/01/saida/*.txt
	rm -r Casos/02/saida/*.txt
	rm -r Casos/03/saida/*.txt
	rm -r Casos/04/saida/*.txt
	rm -r Casos/05/saida/*.txt
	rm -r Casos/06/saida/*.txt
	rm -r Casos/07/saida/*.txt
	rm -r Casos/08/saida/*.txt
	rm -r Casos/09/saida/*.txt
	rm -r Casos/10/saida/*.txt

cleancasosetapa2: 
	rm -r Casos/01/saida/*.txt
	rm -r Casos/02/saida/*.txt
	rm -r Casos/03/saida/*.txt
	rm -r Casos/04/saida/*.txt
	rm -r Casos/05/saida/*.txt
	rm -r Casos/06/saida/*.txt		

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main Casos/1 < Casos/1/entrada.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main Casos/2 < Casos/2/entrada.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main Casos/3 < Casos/3/entrada.txt