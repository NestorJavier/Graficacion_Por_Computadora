#ifndef OBJ
#define OBJ
#include <vector>
#include "Cara.h"
#include <string>
using namespace std;

class Obj
{
	public:
		Obj(string sNombre);
		Obj();
		vector<Cara*> getliCaras();
		string getNombre();
		void setliCaras(vector<Cara*> Caras);
		void setNombre(string sNombre);
		virtual~Obj();
		vector<Cara*> Caras;
	private:
		string sNombre;
};
#endif
