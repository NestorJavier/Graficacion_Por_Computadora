#include "Archivo.h"
#include <vector>
#include "Obj.h"
#include "Vertice.h"
#include <string>
#include <iostream>
using namespace std;

//La clase archivo contine una lista de Objetos y una lista de vertices
Archivo::Archivo(vector<Obj*> Objs, vector<Vertice*> Vertcs)
{
	this->Objs = Objs;
	this->Vertcs = Vertcs;
}

Archivo::Archivo()
{

}

vector<Obj*> Archivo::getliObjs(){return this->Objs;}

vector<Vertice*> Archivo::getVertcs(){return this->Vertcs;}

void Archivo::setliObjs(vector<Obj*> Objs){this->Objs = Objs;}

void Archivo::setVertcs(vector<Vertice*> Vertcs){this->Vertcs = Vertcs;}

Archivo::~Archivo()//Constructor con identificador
{

}
