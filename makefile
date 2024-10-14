OBJS   = main.o cara.o envolvente.o interfaz.o objeto.o vertice.o KDTree.o nodo.o

SOURCE = main.cpp cara.cpp envolvente.cpp interfaz.cpp objeto.cpp vertice.cpp KDTree.cpp nodo.cpp

HEADER = cara.h envolvente.h interfaz.h objeto.h vertice.h KDTree.h nodo.h

OUT = main
CC = g++
FLAGS = -std=c++11 -g -c -Wall
LFLAGS = 

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -o main.o

cara.o: cara.cpp
	$(CC) $(FLAGS) cara.cpp -o cara.o

envolvente.o: envolvente.cpp
	$(CC) $(FLAGS) envolvente.cpp -o envolvente.o

interfaz.o: interfaz.cpp
	$(CC) $(FLAGS) interfaz.cpp -o interfaz.o

objeto.o: objeto.cpp
	$(CC) $(FLAGS) objeto.cpp -o objeto.o

vertice.o: vertice.cpp
	$(CC) $(FLAGS) vertice.cpp -o vertice.o

KDTree.o: KDTree.cpp
	$(CC) $(FLAGS) KDTree.cpp -o KDTree.o
	
nodo.o: nodo.cpp
	$(CC) $(FLAGS) nodo.cpp -o nodo.o

clean:
ifeq ($(OS), Windows_NT)
	del /Q *.o $(OUT).exe
else
	rm -f $(OBJS) $(OUT)
endif