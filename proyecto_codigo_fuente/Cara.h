#ifndef CARA
#define CARA
#include <vector>
#include "Normal.h"
using namespace std;

class Cara
{
	public:
		//Constructor
		Cara(vector <int> liIDVertices,int iNumeroCara);
		Cara();
		vector <int> getliIDVertices();
		int getNumeroCara();
		int getVisible();
		int setVisible(int iVisible);
		//Normal getNormal();
		//Destructor
		Normal normal;
		//vector <int> normal;
		virtual ~Cara();
	private:
		vector <int> liIDVertices;
		int iNumeroCara;
		int iVisible;

};
#endif
