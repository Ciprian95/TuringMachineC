build: main.c
	gcc main.c -o exe
run: exe
	./exe
clean: rm -f exe
