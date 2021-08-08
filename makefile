KKJserver: Asst3.o
	gcc Asst3.o -o KKJserver
Asst3.o:
	gcc -c Asst3.c

clean:
	rm -f KKJserver *.o
