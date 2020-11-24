#include "Cara.h"
#include "Normal.h"
#include <vector>
#include <iostream>
using namespace std;

//La clase cara contiene una lista de Indices, los cuales fungen como identificadores de los vertices
//de esta manera solo se almacenan los identificadores en lugar de guardar una lista con vertices por cada cara.
Cara::Cara(vector <int> liIDVertices,int iNumeroCara)
{
	this->liIDVertices = liIDVertices;
	this->iNumeroCara = iNumeroCara;
}
Cara::Cara()
{

}

vector <int> Cara::getliIDVertices(){return this->liIDVertices;}

int Cara::getNumeroCara(){return this->iNumeroCara;}
int Cara::getVisible(){return this->iVisible;}
int Cara::setVisible(int iVisible){this->iVisible = iVisible;}

//Normal Cara::getNormal(){return this->normal;}

Cara::~Cara() //Destructor
{

}

