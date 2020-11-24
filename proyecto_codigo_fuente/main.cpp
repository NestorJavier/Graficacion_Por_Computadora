#include <cstring>
#include <cstdio>
#include <vector>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "Archivo.h"
#include "Obj.h"
#include "Cara.h"
#include "Vertice.h"
const GLdouble pi = 3.1415926535897932384626433832795;
using namespace std;

//Cargar información de los .OBJ
Archivo cargaArchivo();
void LoadPath();

//funciones auxiliares
void ObtienePunto();
void calculaPuntos();
void InicializaBezier();
void ImprimeClaseArchivo(Archivo nArch);
Archivo nArch = cargaArchivo();
typedef struct 
{
	float x,y,z;
}Vert;

// Constantes de iluminación
float ka = 0.5; 
float Ia = 1.0; 
float kd = 0.5;	
float Il = 1.0; 
// L es el vector que indica la posición del la fuente de luz
Vert L;
//PRP es el punto de vista de perspectiva
Vert PRP;

//POS es un punto que varia durante la ejecución y es la esta variación
//Indica la ruta que el avión sigue durante la ejecución.
Vert Pos, p1, p2, p3, p4;
Vert Pi, Pf;
float m, b, xi, yi, xf, yf;
float a, c, t2, t3, b2, c2, x, y, z, t = 0;


vector<Vert> Path;
static int It = 0;
static GLdouble fovY = 50.0f;
static GLdouble aspect = (double)850.0f/(double)850.0f;
static GLdouble zNear = 5.0;
static GLdouble zFar = 200;
static GLdouble fW, fH;


//Funciones de OpenGL
void init (void);
void display(void);
void spinDisplay(void);
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);

/*Funciones para calcular Normal, superficie visible e iluminación*/
void CalculaNormalVisibilidad();
float iluminacion(int j);
void ActualizaPerspectiva();

int main(int argc, char** argv)
{


    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize (850, 850); 

    glutInitWindowPosition (400, 400);

    glutCreateWindow ("Avión");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;   
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	int itamtOb = (nArch.getliObjs()).size();
	float nuex, nuey, nuez;
	int visible, i;
	GLfloat j;

	calculaPuntos();

	//ObtienePunto();

	int indice, itamvector;
	float x, y, z;
	CalculaNormalVisibilidad();
	GLfloat ColorCons = 1.0/255.0;
	GLfloat Rmod, Gmod, Bmod, RPlano;

	Rmod = ColorCons*(154);
	Gmod = ColorCons*(120);
	Bmod = ColorCons*(40);

	RPlano = ColorCons*(166);
	//GPlano = ColorCons*(120);
	//BPlano = ColorCons*(40);
	

	//Dibujado de la malla
	glColor3f(RPlano, RPlano, RPlano);
  	glBegin(GL_POLYGON);
  	for (GLfloat i = -7.0; i <= 7.0; i += 0.5)
	{
    	     glVertex3f(i, 0, 7.0); glVertex3f(i, 0, -7.0);
    	     glVertex3f(7.0, 0, i); glVertex3f(-7.0, 0, i);
  	}
  	glEnd();

	for (int i = 0; i < itamtOb; i++)
	{
		vector<Cara*> faces = (nArch.getliObjs())[i]->getliCaras();
		int itamtvectorCaras = faces.size();
		{	
			for (int j = 0; j < itamtvectorCaras; j++)
			{

				//cout << " Visibilidad: " <<faces[j]->getVisible() ;
				if(faces[j]->getVisible() == 1)
				{
					float I = iluminacion(j);

					int inumVert = (faces[j]->getliIDVertices()).size();
					for(int k = 0; k < inumVert; k++)
					{

						indice = (faces[j]->getliIDVertices())[k];
						x = nArch.getVertcs()[indice]->getX();
						y = nArch.getVertcs()[indice]->getY();
						z = nArch.getVertcs()[indice]->getZ();

						glColor3f(Rmod*I, Gmod*I, Bmod*I);
						glBegin(GL_POLYGON);
						//cout << (nArch.getliObjs())[i]->getNombre();

		        		glVertex3f (x+Pos.x, y+Pos.y, z+Pos.z);
		        		//glVertex3f (x, y, z);
					}
					glEnd();
				}
			}
		}
	}

     glutSwapBuffers();
     glFlush ();
}


void init (void) 
{
	//LoadPath();
	
/*  select clearing (background) color       */
    //glClearColor (0.01960, 0.09803, 0.4392, 1.0);
	glClearColor (0.0, 0.0, 0.0, 1.0);
/*  initialize viewing values  */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    InicializaBezier();
	
    fH = tan( fovY / 360 * pi ) * zNear;
	fW = fH * aspect;
    //PRP position
    PRP.x = -6.0f;
    PRP.y = 3.0f;
    PRP.z = 10.0f;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
	gluLookAt(PRP.x,PRP.y,PRP.z,0,0,0,0,1,0);
    //glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);


	//Pos = Path[0];
	 L.x=0;	L.y=1;	L.z=1;
}

void InicializaBezier()
{
	t = 0;

	Vert pt11, pt12, pt13, pt14, pt21, pt22, pt23, pt24, pt31, pt32, pt33, pt34, pt41, pt42, pt43, pt44;

	switch (0)
	{
		case 0:
			pt11.x = -5.0; pt11.y = 0.0;  pt11.z = 0.0;
		    pt12.x = 2.96; pt12.y = 3.38; pt12.z = 0.0;
		    pt13.x = -2.96; pt13.y = 3.38; pt13.z = 0.0;
		    pt14.x = 5.0; pt14.y = 0.0; pt14.z = 0.0;

		    p1 = pt11; p2 = pt12, p3 = pt13; p4 = pt14;
		break;
		case 1:
			pt21.x = -15.0; pt21.y = 0.0;  pt21.z = 0.0;
		    pt22.x = -7.5; pt22.y = 15.0; pt22.z = 0.0;
		    pt23.x = 7.5; pt23.y = 15.0; pt23.z = 0.0;
		    pt24.x = 15.0; pt24.y = 0.0; pt24.z = 0.0;

			p1 = pt21; p2 = pt22, p3 = pt23; p4 = pt24;
		break;
		case 2:
			pt31.x = -15.0; pt31.y = 0.0;  pt31.z = 0.0;
		    pt32.x = -7.5; pt32.y = 17.0; pt32.z = 0.0;
		    pt33.x = 7.5; pt33.y = 17.0; pt33.z = 0.0;
		    pt34.x = 15.0; pt34.y = 0.0; pt34.z = 0.0;

			p1 = pt31; p2 = pt32, p3 = pt33; p4 = pt34;
		break;
		case 3:
			pt41.x = -15.0; pt41.y = 0.0;  pt41.z = 0.0;
		    pt42.x = -7.5; pt42.y = -17.0; pt42.z = 0.0;
		    pt43.x = 7.5; pt43.y = -17.0; pt43.z = 0.0;
		    pt44.x = 15.0; pt44.y = 0.0; pt44.z = 0.0;

			p1 = pt41; p2 = pt42, p3 = pt43; p4 = pt44;
		break;
	}
}


Archivo cargaArchivo()
{
	FILE* arch;
	Archivo* auxArch = new Archivo();

	char *chNom = new char[30];
	int inumCara = 1, inObj = 0;
	vector<Obj*> Objss;
	vector<Vertice*> Verts;
	string sNom = "modeloAvionOrigen.obj";
	strcpy(chNom, sNom.c_str());
	arch = fopen(chNom,"r");

	if(arch)
	{
		//variable donde se almacenan uno a uno temporalmente los caracteres del archivo
		char c;

		while (!feof(arch))//Mientras no sea fin de archivo
		{
		    if(c != 'o')
            {
            	//getc(arch); obtiene un caracter del archivo y a su vez avanza una posición en el archivo
                c = getc(arch);
                fflush(arch);
			}
			switch(c)
			{
				case '#'://Se omite la linea que comienza con este caracter
				{
					while(c != '\n')
    	  			{
    	  				c = getc(arch);
    	  				fflush(arch);
					}
				}
				break;
				case 'o'://La 'o' indica el nombre del objeto
				{
					vector<Cara*> Cars;
					string nombreObj;
				    c = getc(arch);
				    fflush(arch);

				    while (c!='\n')
				    {
				    	c = getc(arch);
				     	nombreObj += c;
				    }
				    ///if(nombreObj != "BezierCurve")
				    	Obj *auxObj = new Obj(nombreObj);
				    	cout << nombreObj;

				    while (!feof(arch) && c !='o')//Mientras no sea fin de archivo y el caracter sea diferente del caracter 'o'
                    {
                        if(c != 'f')
                        {
                            c = getc(arch);
                            fflush(arch);
                        }
                        switch(c)
                        {
                            case 'v'://Si es v quiere decir que es vertice
                            {
                                float x,y,z;

                                fscanf(arch,"%f",&x);
                                fscanf(arch,"%f",&y);
                                fscanf(arch,"%f",&z);
                                Vertice *auxVertice = new Vertice(x, y, z);
                                Verts.push_back(auxVertice);
                            }
                            break;
                            case 'f':
                            {
                                vector <int> liIDVertices;
                                int j = 0;
                                int verId;

                                do
                                {
                                    c = getc(arch); //Asigna la posicion del carcater donde entro a este ciclo
                                    fflush(arch);
                                    if(c == ' ') //Si es espacio
                                    {
                                        fscanf(arch,"%d",&verId); //Lee el entero siguiente, tiene identificador del vertice
                                        liIDVertices.push_back(verId-1);
                                    }

                                }while(c != '\n' && !feof(arch)); //Mientras el caracter no sea salto de linea, ni fin del archivo

                                Cara *auxCara = new Cara(liIDVertices, inumCara);
                                inumCara++;
                                Cars.push_back(auxCara);

                                c = getc(arch);
                                fflush(arch);

                                if (c == 'o' || c == '\377')
                                {
                                    auxObj->setliCaras(Cars);
                                    Objss.push_back(auxObj);
                                }
                            }
                            break;
                        }
                    }
				    inObj++;
				}
				break;
			}
		}
	}
	else
		cout << "No existe un archivo con ese nombre";


	auxArch->setliObjs(Objss);
	auxArch->setVertcs(Verts);

	fclose(arch);
	return *auxArch;
}

void LoadPath()
{
	FILE* arch;

	char *chNom = new char[30];
	string sNom = "Path.obj";
	strcpy(chNom, sNom.c_str());
	arch = fopen(chNom,"r");

	if(arch)
	{
		//variable donde se almacenan uno a uno temporalmente los caracteres del archivo
		char c;

		while (!feof(arch))//Mientras no sea fin de archivo
		{
		    if(c != 'o')
            {
            	//getc(arch); obtiene un caracter del archivo y a su vez avanza una posición en el archivo
                c = getc(arch);
                fflush(arch);
			}
			switch(c)
			{
				case '#'://Se omite la linea que comienza con este caracter
				{
					while(c != '\n')
    	  			{
    	  				c = getc(arch);
    	  				fflush(arch);
					}
				}
				break;
				case 'o'://La 'o' indica el nombre del objeto
				{
					string nombreObj;
				    c = getc(arch);
				    fflush(arch);

				    while (c!='\n')
				    {
				    	c = getc(arch);
				     	nombreObj += c;
				    }
				    cout << nombreObj;

				    while (!feof(arch) && c !='o')//Mientras no sea fin de archivo y el caracter sea diferente del caracter 'o'
                    {
                        if(c != 'f')
                        {
                            c = getc(arch);
                            fflush(arch);
                        }
                        if(c == 'v')
                        {
                            float x,y,z;
                            Vert auxVert;
                            fscanf(arch,"%f",&x);
                            fscanf(arch,"%f",&y);
                            fscanf(arch,"%f",&z);
                            auxVert.x = x;
                            auxVert.y = y;
                            auxVert.z = z;
                            Path.push_back(auxVert);
                        }
                        if (c == '\377')
                        {
                        	break;
                        }

                    }
				}
				break;
			}
		}
	}
	else
		cout << "No existe un archivo con ese nombre";
		
	cout << "Tamaño del Vector " << Path.size() << "\n";
	fclose(arch);
}

void CalculaNormalVisibilidad()
{
	double mag;
	Vert v1,v2;

	vector<Cara*> faces = (nArch.getliObjs())[0]->getliCaras();
	int iNumCaras = faces.size();

	for (int j = 0; j < iNumCaras; j++)
	{

	    int IndiceVrt0 = (nArch.getliObjs())[0]->getliCaras()[j]->getliIDVertices()[0];
	    int IndiceVrt1 = (nArch.getliObjs())[0]->getliCaras()[j]->getliIDVertices()[1];
	    int IndiceVrt2 = (nArch.getliObjs())[0]->getliCaras()[j]->getliIDVertices()[2];
		//cout << "Cara: " <<j << "\n";
		//V_1 = v1 - v0
		v1.x = nArch.getVertcs()[IndiceVrt1]->getX() - nArch.getVertcs()[IndiceVrt0]->getX();
		v1.y = nArch.getVertcs()[IndiceVrt1]->getY() - nArch.getVertcs()[IndiceVrt0]->getY();
		v1.z = nArch.getVertcs()[IndiceVrt1]->getZ() - nArch.getVertcs()[IndiceVrt0]->getZ();

		// V_2 = v2 - v0
		v2.x = nArch.getVertcs()[IndiceVrt2]->getX() - nArch.getVertcs()[IndiceVrt0]->getX();
		v2.y = nArch.getVertcs()[IndiceVrt2]->getY() - nArch.getVertcs()[IndiceVrt0]->getY();
		v2.z = nArch.getVertcs()[IndiceVrt2]->getZ() - nArch.getVertcs()[IndiceVrt0]->getZ();

		float auxA = (v1.y * v2.z) - (v1.z * v2.y);
		float auxB = (v1.z * v2.x) - (v1.x * v2.z);
		float auxC = (v1.x * v2.y) - (v1.y * v2.x);

		mag = sqrt(pow(auxA,2) + pow(auxB,2) + pow(auxC,2));


		(nArch.getliObjs())[0]->getliCaras()[j]->normal.A = (auxA/mag);
		(nArch.getliObjs())[0]->getliCaras()[j]->normal.B = (auxB/mag);
		(nArch.getliObjs())[0]->getliCaras()[j]->normal.C = (auxC/mag);

		int iVis = ((nArch.getliObjs())[0]->getliCaras()[j]->normal.A*PRP.x)
				 + ((nArch.getliObjs())[0]->getliCaras()[j]->normal.B*PRP.y)
				 + ((nArch.getliObjs())[0]->getliCaras()[j]->normal.C*PRP.z);

		if(iVis >= 0)
			(nArch.getliObjs())[0]->getliCaras()[j]->setVisible(1);
		else
			(nArch.getliObjs())[0]->getliCaras()[j]->setVisible(0);
	}
}

float iluminacion(int j)
{
	float i_dif, i_amb, NL;

	//Illumination model: I = k_a*I_a + k_d*I_l*(N.L)

	//Calculate ambient illumination
	i_amb = ka * Ia;
	//N.L
	NL = ((nArch.getliObjs())[0]->getliCaras()[j]->normal.A * L.x)
		   + ((nArch.getliObjs())[0]->getliCaras()[j]->normal.B * L.y)
		   + ((nArch.getliObjs())[0]->getliCaras()[j]->normal.C * L.z); 
	//Calculate ambient illumination
	i_dif = kd*Il*NL;

	return i_amb+i_dif;
}

void mouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay);//Idle es un evento que se ejecuta cuando no pasa nada
         break;
      case GLUT_MIDDLE_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;
      default:
         break;
   }
}

void spinDisplay(void)
{
	It++;
	if (It > Path.size())
		It = 0;
	
	glutPostRedisplay();
}
void ObtienePunto()
{
	Pos = Path[It];
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 100:                            // tecla "d"
			PRP.x += 0.1;
			ActualizaPerspectiva();
		break;
		case 97:                            // tecla "a"
			PRP.x -= 0.1;
            ActualizaPerspectiva();
		break;
		case 119:                           // tecla "w"
			PRP.y += 0.1;
            ActualizaPerspectiva();
		break;
		case 115:                           // tecla "s"
			PRP.y -= 0.1;
            ActualizaPerspectiva();
		break;
		case 45:                            // tecla "+"
			PRP.z += 0.1;
            ActualizaPerspectiva();
		break;
		case 43:                            // tecla "-"
			PRP.z -= 0.1;
            ActualizaPerspectiva();
		break;
	}
}
void ActualizaPerspectiva()
{
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glFrustum( -fW, fW, -fH, fH, zNear, zFar );
	gluLookAt(PRP.x,PRP.y,PRP.z,0,0,0,0,1,0);
    glutPostRedisplay();
}

void calculaPuntos()
{
	if(t < 1)
    {
        a = (1-t);
        b = pow(a, 2);
        c = b * a;
        t2 = pow(t, 2);
        t3 = t2*t;
        b2 = 3*t*b;
        c2 = 3*t2*a;        
        Pos.x = c*p1.x + b2*p2.x + c2*p3.x + t3*p4.x;
        Pos.y = c*p1.y + b2*p2.y + c2*p3.y + t3*p4.y;
        Pos.z = c*p1.z + b2*p2.z + c2*p3.z + t3*p4.z;
        
        t += 0.01;
        if(t >= 1)
        	t = 0;

    }
}

void calculaPendiente()
{
	if(t > 0.05)
	{

	}
}
