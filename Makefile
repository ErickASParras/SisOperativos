main: bin/main.o bin/Queue.o
	gcc -o $@ $^

bin/main.o: main.c | bin fatal.h Queue.h
	gcc -c -o $@ $^
bin/Queue.o: Queue.c | bin fatal.h Queue.h
	gcc -c -o $@ $^

bin:
	mkdir bin
clean:
	rm -rf bin main