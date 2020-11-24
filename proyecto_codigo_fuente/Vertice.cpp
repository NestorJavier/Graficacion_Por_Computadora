#include "Vertice.h"
#include <iostream>
using namespace std;


Vertice::Vertice(float x,float  y,float  z)//Constructor con identificador
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//Metodos de acceso
float Vertice::getX(){return this->x;}
float Vertice::getY(){return this->y;}
float Vertice::getZ(){return this->z;}

float Vertice::setX(float x){this->x = x;}
float Vertice::setY(float y){this->y = y;}
float Vertice::setZ(float z){this->z = z;}

Vertice::~Vertice( ) //Destructor
{

}