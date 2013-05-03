/*
	Jesus Torres - 0640386
	Alfredo Gallardo - 0630563

*/

#ifndef EDIFICIO_H
#define EDIFICIO_H

#include <GL/gl.h>										
#include <GL/glu.h>		
#include "../../staticAgent/include/staticAgent.h"
#include "../../Resources/Libs/Materiales.h"

#include "../../Resources/Libs/Cargador_Obj.h"
#include "../../Resources/Libs/Texturas_2D.h"
#include <math.h>

using namespace std;
class Edificio: public staticAgent{
	public:
	//Funciones
		Edificio(int Tipo);
		virtual ~Edificio();
		void Assign(GLfloat x,GLfloat y,GLfloat z);
		void Update(GLfloat Actualz);
		void Draw();

        void Draw_Shadow();
        void LoadTexture(const char *direccion);
		bool Collision(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
	bool Collision2(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
    //Variable
        c_material *material;
        GLuint texture[6];        
        GLuint lista;
        int Tipo;
};  

#endif
