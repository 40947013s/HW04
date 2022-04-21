all: hw0401.o func0401.c hw0402.o func0402.c
	gcc func0401.c hw0401.o -o hw0401
	gcc func0402.c hw0402.o -o hw0402
	
hw0401: hw0401.c
	gcc -c hw0401.c -o hw0401.o 
	gcc -shared hw0401.o -o libhw0401.so

hw0402: hw0402.c
	gcc -c hw0402.c -o hw0402.o 
	gcc -shared hw0402.o -o libhw0402.so