all: hw0401.o func0401.c
	gcc func0401.c hw0401.o -o hw0401
	
hw0401: hw0401.c
	gcc -c hw0401.c -o hw0401.o 
	gcc -shared hw0401.o -o libhw0401.so
