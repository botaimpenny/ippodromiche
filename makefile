ippodrom: ippo.o main.o
	gcc ippo.o main.o -o ippodrom
ippo.o: ipp.c
	gcc -c ipp.c -o ippo.o
main.o: main.c
	gcc -c main.c -o main.o
