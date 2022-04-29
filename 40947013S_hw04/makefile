all: hw0401.o func0401.c hw0402.o func0402.c hw0403.o hw0404.o func0404.c
	gcc func0401.c hw0401.o -o hw0401
	gcc func0402.c hw0402.o -o hw0402
	gcc hw0403.o -o hw0403 -lm	
	gcc func0404.c hw0404.o -o hw0404

hw0401: hw0401.c
	gcc -c hw0401.c -o hw0401.o 
	gcc -shared hw0401.o -o libhw0401.so

hw0402: hw0402.c
	gcc -c hw0402.c -o hw0402.o 
	gcc -shared hw0402.o -o libhw0402.so

hw0403: hw0403.c
	gcc -c hw0403.c -o hw0403.o -lm
	gcc -shared hw0403.o -o libhw0403.so

hw0404: hw0404.c
	gcc -c hw0404.c -o hw0404.o -lm
	gcc -shared hw0404.o -o libhw0404.so