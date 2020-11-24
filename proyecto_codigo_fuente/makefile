hello: Vertice.o Normal.o Cara.o Obj.o Archivo.o main.o
	g++ main.o Vertice.o Normal.o Cara.o Obj.o Archivo.o -lglut -LGLU -lGLU -lGL -o main

main.o: main.cpp
	g++ -c main.cpp

Vertice.o: Vertice.cpp
	g++ -c Vertice.cpp

Normal.o: Normal.cpp
	g++ -c Normal.cpp

Cara.o: Cara.cpp
	g++ -c Cara.cpp

Obj.o: Obj.cpp
	g++ -c Obj.cpp

Archivo.o: Archivo.cpp 
	g++ -c Archivo.cpp

clean:
	rm -rf *.o
