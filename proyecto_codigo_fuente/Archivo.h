#ifndef ARCHIVO
#define ARCHIVO
//#include <list>
#include <vector>
#include "Obj.h"
#include "Cara.h"
#include "Vertice.h"
#include <string>
using namespace std;

class Archivo
{
	public:
		Archivo(vector<Obj*> Objs, vector<Vertice*> Vertcs);
		Archivo();
		vector <Obj*> getliObjs();
		vector<Vertice*> getVertcs();
		void setliObjs(vector<Obj*> Objs);
		void setVertcs(vector<Vertice*> Vertcs);
		virtual~Archivo();
	private:
		vector<Obj*> Objs;
		vector<Vertice*> Vertcs;
};
#endif
