/*
	Jesus Torres - 0640386
	Alfredo Gallardo - 0630563

*/

#ifndef ANILLO_H
#define ANILLO_H

#include <GL/gl.h>										
#include <GL/glu.h>		
#include "../../staticAgent/include/staticAgent.h"
#include "../../Resources/Libs/Materiales.h"

// Clase Anillo usada para determinar los objetos que incrementan los puntos
class Anillo: public staticAgent{
	public:
	//Funciones
		Anillo();
		virtual ~Anillo();
		void Assign(GLfloat x,GLfloat y,GLfloat z);
		void Update(GLfloat Actualz);
		void Draw();

        void Draw_Shadow();

		bool Collision(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
		bool Collision2(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
    //Variable
        c_material *material;
        GLuint lista;
};

#endif
