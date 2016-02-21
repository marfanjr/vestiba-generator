all: mfvj11-autor mfvj11-realizador

mfvj11-autor: mfvj11-autor.o mfvj11-bib.o
	gcc mfvj11-autor.o mfvj11-bib.o -o mfvj11-autor

mfvj11-autor.o: mfvj11-autor.c mfvj11-bib.h
	gcc -c -g mfvj11-autor.c -o mfvj11-autor.o
mfvj11-realizador: mfvj11-realizador.o mfvj11-bib.o
	gcc mfvj11-realizador.o mfvj11-bib.o -o mfvj11-realizador

mfvj11-realizador.o: mfvj11-realizador.c mfvj11-bib.h
	gcc -c -g mfvj11-realizador.c -o mfvj11-realizador.o

mfvj11-bib.o: mfvj11-bib.c mfvj11-bib.h
	gcc -c -g mfvj11-bib.c -o mfvj11-bib.o
clean:
	rm -rf *.o 

