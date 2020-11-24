#ifndef VERTICE
#define VERTICE


class Vertice
{
	public:
		//Constructor
		Vertice(float x,float  y,float  z);
		float getX();
		float getY();
		float getZ();
		float setX(float x);
		float setY(float y);
		float setZ(float z);
		virtual ~Vertice(); 
	private:
		float x, y, z;
};
#endif