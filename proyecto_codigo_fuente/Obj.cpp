#include "Obj.h"
#include "Cara.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//Esta clase contiene una lista de caras y el nombre correspondiente al objeto
Obj::Obj(string sNombre)
{
	this->sNombre = sNombre;
}

Obj::Obj()
{

}

vector<Cara*> Obj::getliCaras(){return this->Caras;}

string Obj::getNombre(){return this->sNombre;}

void Obj::setliCaras(vector<Cara*> Caras){this->Caras = Caras;}

void Obj::setNombre(string sNombre){this->sNombre = sNombre;}

Obj::~Obj()//Constructor con identificador
{

}
